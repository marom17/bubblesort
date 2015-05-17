#ifndef MONITEURBUBBLE_H
#define MONITEURBUBBLE_H

#include <QSemaphore>

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
        mutex->acquire();
        if(nbAttente < nbMaxAttente){
            mutex->release();
            attenteTrieurs->acquire();
        }else{
            mutex->release();
        }
    }

    void libereTrie(bool fini){
        mutex->acquire();
        estFini = fini;
        while(nbAttente-- > 0){
            attentePrincipal->release();
        }
        mutex->release();
    }

    void libereTrie(){
        libereTrie(estFini);
    }
};

#endif // MONITEURBUBBLE_H
