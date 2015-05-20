/*
 * Les semaphores debut et fin sont differentes.
 * Un thread devra avoir un semaphore du voisin pour pouvoir le release
 */
#ifndef SORTTHREAD
#define SORTTHREAD

#include <QDebug>
#include <QThread>
#include <QSemaphore>

#include <iostream>
using namespace std;

//#include "moniteurcasepartagee.h"
#include "moniteurbubble.h"
#include "bubblesort.h"

template<typename T>
class SortThread : public QThread
{
private:
    bool inactivite; // indique s'il y a eu un swap avec une case partagee
    qint64 taille;
    T* tableau;
    BubbleSort<T> sorter;

    QSemaphore *debut;
    QSemaphore *fin;
    MoniteurBubble *moniteurControl;

    virtual void run() Q_DECL_OVERRIDE{
        threadSort();
    }
public:
    void threadSort(){
        bool tmpFin ;
        do{
            moniteurControl->affichageProteger("je bosse\n");
            inactivite = true;
            // vérifie si ce n'est pas le premier thread
            if(debut != nullptr){
                sorter.sort(tableau+1, taille-1);
                // attend que son premier collegue finisse de trier
                debut->acquire();
                // si la case commune est plus grande que ca suivante, swap les valeurs
                if(tableau[0] > tableau[1]){
                    T tmp = tableau[0];
                    tableau[0] = tableau[1];
                    tableau[1] = tmp;
                    // indique qu'il y a eu un swap
                    cout << "On en a pas fini\n";
                    inactivite = false;
                }
            }else{
                sorter.sort(tableau, taille);
            }
            // verifie si ce n'est pas le dernier thread
            if(fin != nullptr){
                fin->release();
            }
            moniteurControl->affichageProteger("j'ai fini de bosser\n");
            tmpFin = moniteurControl->attenteVerification();
            if(!tmpFin)
                moniteurControl->affichageProteger("C'est fini pour de bon\n");
        }while(!tmpFin);
    }
    SortThread(T* tableau, qint64 taille, MoniteurBubble *moniteurControl){
        this->taille = taille;

        this->tableau = tableau;

        this->moniteurControl = moniteurControl;
        this->debut = nullptr;
        this->fin   = nullptr;

    }

    ~SortThread(){
    }

    void setDebut(QSemaphore *debut){
        this->debut = debut;
    }
    void setFin(QSemaphore *fin){
        this->fin = fin;
    }

    bool getInactivite(){
        cout << inactivite << "\n";
        return inactivite;
    }
};

#endif // SORTTHREAD

