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
     * que l'on met a vrai lorsque qu'il y eu un swap
     * ainsi, on ne fait qu'une seule lecture au lieu
     * de vérifier chaque thread
     */
    bool inactivite; // indique s'il y a eu un swap avec une case partagee
    int indexDebut;
    int indexFin;
    T *tableau;

    MoniteurBubble *moniteurControl;
    MoniteurCasePartagee *moniteurDebut;
    MoniteurCasePartagee *moniteurFin;

    virtual void run() Q_DECL_OVERRIDE{
        while(!moniteurControl->attenteVerification()){
            inactivite = true;
            // vérifie si ce n'est pas le premier thread
            if(moniteurDebut != nullptr){
                sort(tableau+indexDebut+1, indexFin-indexDebut);
                // attend que son premier collegue finisse de trier
                moniteurDebut->attenteCollegues();
                // si la case commune est plus grande que ca suivante, swap les valeurs
                if(tableau[indexDebut] > tableau[indexDebut+1]){
                    tableau[indexDebut]   = tableau[indexDebut] ^ tableau[indexDebut+1];
                    tableau[indexDebut+1] = tableau[indexDebut] ^ tableau[indexDebut+1];
                    tableau[indexDebut]   = tableau[indexDebut] ^ tableau[indexDebut+1];
                    // indique qu'il y a eu un swap
                    inactivite = false;
                }
            }
            else{
                sort(tableau+indexDebut, indexFin-indexDebut);
            }

            // verifie si ce n'est pas le dernier thread
            if(moniteurFin != nullptr){
                // attend son second collegue finisse de trier
                moniteurFin->attenteCollegues();
            }
        }
    }

public:
    BubbleSortThreaded(int indexDebut, int indexFin, T *tableau,
                       MoniteurBubble*&moniteurControl,
                       MoniteurCasePartagee *moniteurDebut,
                       MoniteurCasePartagee *moniteurFin) {
        inactivite = true;

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
