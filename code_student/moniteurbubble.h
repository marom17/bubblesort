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

public:
    MoniteurBubble(int nbMaxAttente){
        this->nbMaxAttente = nbMaxAttente;
        nbAttente = 0;
        mutex = new QSemaphore(1);
        attentePrincipal = new QSemaphore(0);
        attenteTrieurs = new QSemaphore(0);
        estFini = false;
    }

    ~MoniteurBubble(){
        delete mutex;
        delete attentePrincipal;
        delete attenteTrieurs;
    }

    bool attenteVerification(){
        mutex->acquire();
        if(++nbAttente >= nbMaxAttente){
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

        for(int i = 0; i < nbMaxAttente; i++){
            attentePrincipal->release();
        }

        mutex->release();
    }

    void affichageProteger(string msg){
        mutex->acquire();
        cout << msg;
        mutex->release();
    }
};

#endif // MONITEURBUBBLE_H
