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

using namespace std;

//#define TABSIZE 10000000
#define TABSIZE 10

SortTester::SortTester()
{
}
void SortTester::test(int tabsize,int nbThread)
{
    srand(time(0));

    int *tab = new int[tabsize];

    for(qint64 i=0;i<tabsize;i++)
        tab[i] = rand();

    cout << endl;
    for(int i = 0; i < tabsize; i++)
        cout << tab[i] << endl;
    cout << endl;

    BubbleSortThreaded<int> *sorteur;
    sorteur = new BubbleSortThreaded<int>(nbThread);
    sorteur->sort(tab,tabsize);

    cout << endl;
    for(int i = 0; i < tabsize; i++)
        cout << tab[i] << endl;
    cout << endl;

    /*
    BubbleSort<int> sorter;

    sorter.sort(tab,TABSIZE);

    */

    int initial = tab[0];
    bool error  = false;

    for(qint64 i=0;i<tabsize;i++)
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
