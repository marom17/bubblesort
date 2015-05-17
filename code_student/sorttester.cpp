#include "sorttester.h"

#include <QCoreApplication>
#include <time.h>
#include <iostream>
#include <QtMath>
#include <QVector>
#include <QThread>

#include "bubblesort.h"
#include "bubblesortthreaded.h"
#include "time.h"


//#define TABSIZE 10000000
#define TABSIZE 10

MoniteurBubble *moniteurControl;
MoniteurCasePartagee *moniteurDebut;
MoniteurCasePartagee *moniteurFin;

SortTester::SortTester()
{
}
void SortTester::test(int tabsize,int nbThread)
{
    srand(time(0));

    int *tab = new int[TABSIZE];

    for(qint64 i=0;i<TABSIZE;i++)
        tab[i] = rand();

    BubbleSortThreaded<int> *sorteur;
    sorteur = new BubbleSortThreaded<int>(nbThread);
    sorteur->sort(tab,tabsize);

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

//    //Supression du tableau de thread
//    for(int i=0;i<nbThread;i++){
//        BubbleSortThreaded<int>* temp;
//        temp = tabThread.front();
//        tabThread.pop_front();
//        delete temp;
//    }
}
