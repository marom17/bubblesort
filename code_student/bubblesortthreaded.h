#ifndef BUBBLESORTTHREADED_H
#define BUBBLESORTTHREADED_H

#include <isort.h>
#include <QDebug>
#include <QThread>
#include <iostream>
using namespace std;

//#include "moniteurcasepartagee.h"
#include "moniteurbubble.h"
#include "sortthread.h"

template<typename T>
class BubbleSortThreaded : public ISort<T>
{

private:
    int nbThread;
    QVector<SortThread<T>* > tabThread;
    QVector<QSemaphore* > tabSem;

public:
    BubbleSortThreaded(int nbThread) {
        this->nbThread=nbThread;
    }

    void sort(T tab[], qint64 size){
        //évite de lancer trop de thread inutilement
        if(size < nbThread){
            nbThread = size;
        }

        int nbParThread = size / nbThread;
        int inegalite = size % nbThread;

        // crée une table de semaphore
        tabThread.resize(nbThread);
        tabSem.resize(nbThread-1);

        for(int i = 0; i < nbThread-1; i++){
            tabSem[i] = new QSemaphore(0);
        }

        MoniteurBubble controleur(nbThread);
        //Disspatching
        //debut
        int indexSuivant = 0;
        if(inegalite > 0){
            tabThread[0] = new SortThread<T>(tab, nbParThread + 1, &controleur);
            inegalite--;
            indexSuivant += nbParThread + 1;
        }else{
            tabThread[0] = new SortThread<T>(tab, nbParThread, &controleur);
            indexSuivant += nbParThread;
        }


        cout << endl;
        for(int i = 0; i < indexSuivant; i++)
            cout << tab[i] << endl;
        cout << endl;

        //regarde s'il y a plus d'un thread
        if(nbThread > 1){
            tabThread[0]->setFin(tabSem[0]);
        }
        //milieu
        for(int i = 1; i < nbThread-1; i++){
            T *tmp = tab + indexSuivant - 1;
            cout <<  endl;
            if(inegalite > 0){
                for(int i = 0; i < nbParThread + 2; i++)
                    cout << tmp[i] << endl;

                tabThread[i] = new SortThread<T>(tab + indexSuivant - 1, nbParThread + 2, &controleur);
                indexSuivant += nbParThread + 1;
                inegalite--;
            }else{
                for(int i = 0; i < nbParThread + 1; i++)
                    cout << tmp[i] << endl;

                tabThread[i] = new SortThread<T>(tab + indexSuivant - 1, nbParThread + 1, &controleur);
                indexSuivant += nbParThread;
            }
            cout << endl;
            tabThread[i]->setDebut(tabSem[i-1]);
            tabThread[i]->setFin(tabSem[i]);
        }
        //fin
        if(nbThread > 1){
            T *tmp = tab + indexSuivant - 1;
            cout << endl;
            for(int i = 0; i < nbParThread + 1; i++)
                cout << tmp[i] << endl;
            cout << endl;
            tabThread[nbThread-1] = new SortThread<T>(tab + indexSuivant - 1, nbParThread + 1, &controleur);
            tabThread[nbThread-1]->setDebut(tabSem.last());
        }

        //Démarrage threads
        for(int i=0;i<nbThread;i++){
            tabThread[i]->start(QThread::NormalPriority);
        }

        //Gestion des threads
        bool fin;
        int tmp = 0;
        do{
            fin = true;
            controleur.attenteFinTrie();
            for(int i = 0; i < nbThread; i++){
                if(!tabThread[i]->getInactivite()){
                    fin = false;
                }
            }
            controleur.libereTrie(fin);
            cout << ++tmp <<"\n";
        }while(!fin);
        controleur.affichageProteger("je sors\n");

        // détruit les thread
        for(int i = 0; i < nbThread; i++){
            tabThread[i]->wait();
            SortThread<T>* tmp = tabThread[i];
            delete tmp;
        }

        // détruit les semaphore
        for(int i = 0; i < nbThread-1; i++){
            QSemaphore *tmp = tabSem[i];
            delete tmp;
        }
    }




};

#endif // BUBBLESORTTHREADED_H
