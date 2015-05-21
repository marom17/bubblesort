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
    int fifo;
    bool estFini;
    bool estLiberer;

public:
    MoniteurBubble(int nbMaxAttente){
        this->nbMaxAttente = nbMaxAttente;
        nbAttente = 0;
        mutex = new QSemaphore(1);
        attentePrincipal = new QSemaphore(0);
        attenteTrieurs = new QSemaphore(0);
        estFini = false;
        estLiberer = true;
        fifo = 0;
    }

    ~MoniteurBubble(){
        delete mutex;
        delete attentePrincipal;
        delete attenteTrieurs;
    }

    bool attenteVerification(QSemaphore *lol){
        while(!estLiberer);
        mutex->acquire();
        if(++nbAttente == nbMaxAttente){
            attenteTrieurs->release();
        }
        //cout << nbAttente << "\n";
        mutex->release();
        attentePrincipal->acquire();
        //cout << "\nliberer, delivrer\n\n";
        mutex->acquire();
        //if(lol == nullptr)
            //cout << "le premier est liberer avant l'heure\n";
        bool tmp = estFini;
        if(--nbAttente == 0){
            estLiberer = true;
        }
        mutex->release();
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
