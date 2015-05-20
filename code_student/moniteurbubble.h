#ifndef MONITEURBUBBLE_H
#define MONITEURBUBBLE_H

#include <QSemaphore>

#include <iostream>
using namespace std;

class MoniteurBubble
{
private:
    QSemaphore *mutex;
    QSemaphore *attentePrincipal;
    QSemaphore *attenteTrieurs;
    int nbMaxAttente;
    int nbAttente;
    bool estFini;

    bool test;

public:
    MoniteurBubble(int nbMaxAttente){
        this->nbMaxAttente = nbMaxAttente;
        nbAttente = 0;
        mutex = new QSemaphore(1);
        attentePrincipal = new QSemaphore(0);
        attenteTrieurs = new QSemaphore(0);
        estFini = false;

        test = false;
    }

    ~MoniteurBubble(){
        delete mutex;
        delete attentePrincipal;
        delete attenteTrieurs;
    }

    bool attenteVerification(){
        mutex->acquire();
        if(++nbAttente >= nbMaxAttente){
            if(test){
                cout << "Gros probleme =============\n";
            }
            test = true;
            attenteTrieurs->release();
        }
        mutex->release();
        attentePrincipal->acquire();
        mutex->acquire();
        bool tmp = estFini;
        mutex->release();
        return tmp;
    }

    void attenteFinTrie(){
        attenteTrieurs->acquire();
    }

    void libereTrie(bool fini){
        mutex->acquire();
        estFini = fini;
        while(nbAttente > 0){
            attentePrincipal->release();
            nbAttente--;
        }

        if(nbAttente != 0){
            cout  << "Probleme =====================\n";
        }else{
            test = false;
        }

        mutex->release();
    }

    void libereTrie(){
        libereTrie(estFini);
    }
};

#endif // MONITEURBUBBLE_H
