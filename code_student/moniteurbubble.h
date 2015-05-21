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
    QSemaphore *attenteLiberation;
    int nbMaxAttente;
    int nbAttente;
    int nbAttenteFifo;
    bool estFini;
    bool estLiberer;

public:
    MoniteurBubble(int nbMaxAttente){
        this->nbMaxAttente = nbMaxAttente;
        nbAttente = 0;
        nbAttenteFifo = 0;
        mutex = new QSemaphore(1);
        attentePrincipal = new QSemaphore(0);
        attenteTrieurs = new QSemaphore(0);
        attenteLiberation = new QSemaphore(0);
        estFini = false;
        estLiberer = true;
    }

    ~MoniteurBubble(){
        delete mutex;
        delete attentePrincipal;
        delete attenteTrieurs;
    }

    bool attenteVerification(){
        mutex->acquire();
        while(!estLiberer){
            mutex->release();
            nbAttenteFifo++;
            attenteLiberation->acquire();
        }
        if(++nbAttente == nbMaxAttente){
            attenteTrieurs->release();
        }
        if(nbAttenteFifo > 0){
            nbAttenteFifo--;
            attenteLiberation->release();
        }else{
            mutex->release();
        }
        attentePrincipal->acquire();
        mutex->acquire();
        bool tmp = estFini;
        if(--nbAttente == 0){
            estLiberer = true;
        }
        if(nbAttenteFifo > 0){
            nbAttenteFifo--;
            attenteLiberation->release();
        }else{
            mutex->release();
        }
        return tmp;
    }

    void attenteFinTrie(){
        attenteTrieurs->acquire();
    }

    void libereTrie(bool fini){
        mutex->acquire();
        estFini = fini;
        int i;
        for(i = 0; i < nbMaxAttente; i++){
            attentePrincipal->release();
        }
        estLiberer = false;
        mutex->release();
    }

    void affichageProteger(string msg){
        mutex->acquire();
        cout << msg;
        mutex->release();
    }

    void affichageTabProteger(int *tab, int taille){
        mutex->acquire();
        for(int i = 0; i < taille; i++){
            cout << tab[i] << " ";
        }
        cout << "\n";
        mutex->release();
    }
};

#endif // MONITEURBUBBLE_H
