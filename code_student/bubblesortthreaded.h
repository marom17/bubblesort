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

    MoniteurBubble *moniteurControl;
    MoniteurCasePartagee *moniteurDebut;
    MoniteurCasePartagee *moniteurFin;

    virtual void run() Q_DECL_OVERRIDE{

    }

public:
    BubbleSortThreaded(int indexDebut, int indexFin, T *tableau,
                       MoniteurBubble*&moniteurControl,
                       MoniteurCasePartagee *moniteurDebut,
                       MoniteurCasePartagee *moniteurFin) {
        inactivite = false;

        this->indexDebut = indexDebut;
        this->indexFin = indexFin;

        this->tableau = tableau;

        this->moniteurDebut = moniteurDebut;
        this->moniteurFin   = moniteurFin;
    }



    virtual void sort(T a[], qint64 size){
        for (int c = size - 1 ; c > 0; --c){
            for (int d = 0 ; d < c; ++d){
                if (tableau[d] > tableau[d+1]){
                    tableau[d]   = tableau[d] ^ tableau[d+1];
                    tableau[d+1] = tableau[d] ^ tableau[d+1];
                    tableau[d]   = tableau[d] ^ tableau[d+1];
                }
            }
        }
    }

    bool getInactivite(){
        return inactivite;
    }
};

#endif // BUBBLESORTTHREADED_H
