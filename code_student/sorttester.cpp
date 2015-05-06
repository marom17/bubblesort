#include "sorttester.h"

#include <QCoreApplication>
#include <time.h>
#include <iostream>

#include "bubblesort.h"
#include "bubblesortthreaded.h"

//#define TABSIZE 10000000
#define TABSIZE 10

SortTester::SortTester()
{
}

void SortTester::test()
{
    srand(time(0));

    int *tab = new int[TABSIZE];

    for(qint64 i=0;i<TABSIZE;i++)
        tab[i] = rand();

    BubbleSort<int> sorter;

    sorter.sort(tab,TABSIZE);

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
}
