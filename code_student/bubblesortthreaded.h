#ifndef BUBBLESORTTHREADED_H
#define BUBBLESORTTHREADED_H

#include <isort.h>
#include <QDebug>
#include <QThread>

#include "moniteurcasepartagee.h"
#include "moniteurbubble.h"

template<typename T>
class BubbleSortThreaded : public ISort<T>, QThread
{
private:
    /*
     * Ce serait pas mieux d'avoir un bool static
     * que l'on met à vrai lorsque qu'il y eu un swap
     * ainsi, on ne fait qu'une seule lecture au lieu
     * de vérifier chaque thread
     */
    bool inactivite;
    int indexDebut;
    int indexFin;
    T *tableau;

    MoniteurBubble &moniteurControl;
    MoniteurCasePartagee &moniteur1;
    MoniteurCasePartagee &moniteur2;

    virtual void run() Q_DECL_OVERRIDE{

    }

public:
    BubbleSortThreaded(int indexDebut, int indexFin, T *tableau, MoniteurBubble &moniteurControl, MoniteurCasePartagee &moniteurCase1, MoniteurCasePartagee &moniteurCase2) {
        inactivite = false;

        this->indexDebut = indexDebut;
        this->indexFin = indexFin;

        this->tableau = tableau;

        this->moniteur1 = moniteur1;
        this->moniteur2 = moniteur2;
    }



    virtual void sort(T a[], qint64 size)
    {
        qDebug() << " Doing nothing :-) ";
    }

    bool getInactivite(){
        return inactivite;
    }
};

#endif // BUBBLESORTTHREADED_H
