/*
 -----------------------------------------------------------------------------------
 Fichier     : sorththread.h
 Auteur(s)   : Domingues Pedrosa João Miguel & Maillard Romain
 Date        : 10.05.2015

 But: Permet de faire un trie concurentiel du type bubble

 Remarque(s) : les sémaphore début et fin corresponde au rendez-vous entre le voisin
 de gauche et de droite, afin que celui qui est en charge du swap (celui de droite)
 puisse faire sa vérification quand l'autre à fini de trier (celui de gauche).
 -----------------------------------------------------------------------------------
*/

#ifndef SORTTHREAD
#define SORTTHREAD

#include <QDebug>
#include <QThread>
#include <QSemaphore>

#include <iostream>
using namespace std;

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
    static bool test;
    void threadSort(){
        bool tmpFin ;
        do{
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
                    inactivite = false;
                }
            }else{
                sorter.sort(tableau, taille);
            }
            // verifie si ce n'est pas le dernier thread
            if(fin != nullptr){
                fin->release();
            }
            tmpFin = moniteurControl->attenteVerification();
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
        return inactivite;
    }
};

#endif // SORTTHREAD

