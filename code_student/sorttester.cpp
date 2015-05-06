#include "sorttester.h"

#include <QCoreApplication>
#include <time.h>
#include <iostream>
#include <QtMath>
#include <QVector>

#include "bubblesort.h"
#include "bubblesortthreaded.h"
#include "time.h"


//#define TABSIZE 10000000
#define TABSIZE 10

SortTester::SortTester()
{
}
void SortTester::test(int tabsize,int nbThread)
{
    srand(time(0));

    int *tab = new int[TABSIZE];

    for(qint64 i=0;i<TABSIZE;i++)
        tab[i] = rand();

    //Création du tableau de thread
    QVector<BubbleSortThreaded<int>*> tabThread;

    for(int i=0;i<nbThread;i++){
        tabThread.push_back(new BubbleSortThreaded<int>());
    }

    //Démarrage threads
    for(int i=0;i<nbThread;i++){
        tabThread.at(i)->start();
    }

    bool entier=false;
    int nbParThread = tabsize/nbThread;

    //On test si il faut rajouter une case au dernier tableau
    if(qCeil(tabsize/nbThread)==nbParThread){
        entier=true;
    }

    //Disspatching
    int indexSuivant=0;
    for(int i=0;i<nbThread-1;i++){
        tabThread.at(i)->sort((tab+indexSuivant),nbParThread);
        indexSuivant+=nbParThread;
    }
    tabThread.last()->sort((tab+indexSuivant),nbParThread+1);


    /*
    BubbleSort<int> sorter;

    sorter.sort(tab,TABSIZE);

    */

    int initial = tab[0];
    bool error  = false;

    for(qint64 i=0;i<TABSIZE;i++)
    {
        if(initial > tab[i])
        {
            error = true;
            break;
        }
        initial = tab[i];
    }

    if(error)
       std::cout << "ERREUR " << std::endl;
    else
       std::cout << "Tri valide " << std::endl;

    delete[] tab;

    //Supression du tableau de thread
    for(int i=0;i<nbThread;i++){
        BubbleSortThreaded<int>* temp;
        temp = tabThread.front();
        tabThread.pop_front();
        delete temp;
    }
}
