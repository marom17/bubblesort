#ifndef SORTTHREAD
#define SORTTHREAD

#include <QDebug>
#include <QThread>

#include "moniteurcasepartagee.h"
#include "moniteurbubble.h"

class SortThread : public QThread
{
private:
    bool inactivite; // indique s'il y a eu un swap avec une case partagee
    int indexDebut;
    int indexFin;
    int *tableau;

    MoniteurBubble *moniteurControl;
    MoniteurCasePartagee *moniteurDebut;
    MoniteurCasePartagee *moniteurFin;

    virtual void run() Q_DECL_OVERRIDE{
        threadSort();
    }
public:
    void threadSort();
    SortThread(int indexDebut, int indexFin, int *tableau): QThread(){

        inactivite = true;

        this->indexDebut = indexDebut;
        this->indexFin = indexFin;

        this->tableau = tableau;

        this->moniteurControl = new MoniteurBubble(4);
        this->moniteurDebut = new MoniteurCasePartagee(4);
        this->moniteurFin   = new MoniteurCasePartagee(4);

    }
    virtual void sort(int a[], qint64 size){
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

#endif // SORTTHREAD

