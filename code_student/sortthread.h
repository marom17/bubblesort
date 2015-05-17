#ifndef SORTTHREAD
#define SORTTHREAD

#include <QDebug>
#include <QThread>

#include <QSemaphore>
#include "moniteurcasepartagee.h"
#include "moniteurbubble.h"

template<typename T>
class SortThread : public QThread
{
private:
    bool inactivite; // indique s'il y a eu un swap avec une case partagee
    qint64 taille;
    T* tableau;

    QSemaphore *debut;
    QSemaphore *fin;
    MoniteurBubble *moniteurControl;

    virtual void run() Q_DECL_OVERRIDE{
        threadSort();
    }
public:
    void threadSort(){
        do{
            inactivite = true;
            // vérifie si ce n'est pas le premier thread
            if(debut != nullptr){
                sort(tableau+1, taille);
                // attend que son premier collegue finisse de trier
                debut->acquire();
                // si la case commune est plus grande que ca suivante, swap les valeurs
                if(tableau[0] > tableau[1]){
                    tableau[0] = tableau[0] ^ tableau[1];
                    tableau[1] = tableau[0] ^ tableau[1];
                    tableau[0] = tableau[0] ^ tableau[1];
                    // indique qu'il y a eu un swap
                    inactivite = false;
                }
            }
            else{
                sort(tableau, taille);
            }

            // verifie si ce n'est pas le dernier thread
            if(fin != nullptr){
                //libere le second collegue
                fin->release();
            }
        }while(!moniteurControl->attenteVerification());
    }
    SortThread(T* tableau, qint64 taille, MoniteurBubble *moniteurControl){

        inactivite = true;

        this->taille = taille;

        this->tableau = tableau;

        this->moniteurControl = moniteurControl;
        this->debut = nullptr;
        this->fin   = nullptr;

    }
    void setDebut(QSemaphore *debut){
        this->debut = debut;
    }
    void setFin(QSemaphore *fin){
        this->fin = fin;
    }
    void sort(T a[], qint64 size){
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

