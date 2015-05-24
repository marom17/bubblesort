/*
 -----------------------------------------------------------------------------------
 Fichier     : bubblesortthread.h
 Auteur(s)   : Domingues Pedrosa João Miguel & Maillard Romain
 Date        : 10.05.2015

 But: Gere le bubble sort de manière concurentiel en créant tout les instances et
 séparant le tableau avec la bonne taille, les lances, vérifie s'ils ont terminer
 et les fait s'arrêter.

 Remarque(s) :
 -----------------------------------------------------------------------------------
*/

#ifndef BUBBLESORTTHREADED_H
#define BUBBLESORTTHREADED_H

#include <isort.h>
#include <QDebug>
#include <QThread>
#include <iostream>
using namespace std;

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

        // crée tout les threads pour les rendez-vous
        // entre chaque threads
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
        //regarde s'il y a plus d'un thread
        if(nbThread > 1){
            tabThread[0]->setFin(tabSem[0]);
        }
        //milieu
        for(int i = 1; i < nbThread-1; i++){
            if(inegalite > 0){
                tabThread[i] = new SortThread<T>(tab + indexSuivant - 1, nbParThread + 2, &controleur);
                indexSuivant += nbParThread + 1;
                inegalite--;
            }else{
                tabThread[i] = new SortThread<T>(tab + indexSuivant - 1, nbParThread + 1, &controleur);
                indexSuivant += nbParThread;
            }
            tabThread[i]->setDebut(tabSem[i-1]);
            tabThread[i]->setFin(tabSem[i]);
        }
        //fin
        if(nbThread > 1){
            tabThread[nbThread-1] = new SortThread<T>(tab + indexSuivant - 1, nbParThread + 1, &controleur);
            tabThread[nbThread-1]->setDebut(tabSem.last());
        }

        //Démarrage threads
        for(int i=0;i<nbThread;i++){
            tabThread[i]->start(QThread::NormalPriority);
        }

        //Gestion des threads
        bool fin;
        do{
            fin = true;
            controleur.attenteFinTrie();
            // vérifie s'il n'y a plus de trie à faire
            for(int i = 0; i < nbThread; i++){
                if(!tabThread[i]->getInactivite()){
                    fin = false;
                    break;
                }
            }
            controleur.libereTrie(fin);
        }while(!fin);

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
