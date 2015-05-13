#ifndef BUBBLESORTTHREADED_H
#define BUBBLESORTTHREADED_H

#include <isort.h>
#include <QDebug>
#include <QThread>

#include "moniteurcasepartagee.h"
#include "moniteurbubble.h"
#include "sortthread.h"

template<typename T>
class BubbleSortThreaded : public ISort<T>
{

private:
    /*
     * Ce serait pas mieux d'avoir un bool static
     * que l'on met a vrai lorsque qu'il y eu un swap
     * ainsi, on ne fait qu'une seule lecture au lieu
     * de vérifier chaque thread
     */
    int tabsize;
    int nbThread;
    T *tableau;
    QVector<SortThread *> tabThread;




public:
    BubbleSortThreaded(int tabsize,int nbThread, T *tableau) {
        this->tableau=tableau;
        this->tabsize=tabsize;
        this->nbThread=nbThread;
    }

    void sort(T tab[], qint64 size){
        bool entier=false;
        int nbParThread = tabsize/nbThread;

        //On test si il faut rajouter une case au dernier tableau
        if(qCeil(tabsize/nbThread)==nbParThread){
            entier=true;
        }

        //Disspatching
        int indexSuivant=0;
        tabThread.push_back(new SortThread(indexSuivant,indexSuivant+nbParThread-1,tableau));
        for(int i=1;i<nbThread-1;i++){
            tabThread.push_back(new SortThread(indexSuivant-1,indexSuivant+nbParThread-1,tableau));
            indexSuivant+=nbParThread;
        }
        if(nbThread>1){
            tabThread.push_back(new SortThread(indexSuivant-1,indexSuivant+nbParThread,tableau));
        }

        //Démarrage threads
        for(int i=0;i<nbThread;i++){
            tabThread[i]->start(QThread::NormalPriority);
        }
    }




};

#endif // BUBBLESORTTHREADED_H
