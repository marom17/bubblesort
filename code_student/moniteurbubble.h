/*
 -----------------------------------------------------------------------------------
 Fichier     : moniteurbubble.h
 Auteur(s)   : Domingues Pedrosa João Miguel & Maillard Romain
 Date        : 10.05.2015

 But: Faire attendre tout les threads sur un rendez-vous, afin que
 le principal puisse voir s'ils ont fini de trier.

 Remarque(s) :
 -----------------------------------------------------------------------------------
*/

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

    void gestionFifo(){
        if(nbAttenteFifo > 0){
            nbAttenteFifo--;
            attenteLiberation->release();
        }else{
            mutex->release();
        }
    }

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

    /**
     * Fait attendre toute les threads pour que le
     * principal puisse vérifier s'il y a eu swap
     * avec une zone commune
     * @brief attenteVerification
     * @return si le thread doit refaire un trie ou pas
     */
    bool attenteVerification(){
        mutex->acquire();
        //regarde si tout le monde a été liberer
        while(!estLiberer){
            mutex->release();
            nbAttenteFifo++;
            attenteLiberation->acquire();
        }
        //vérifie si tout les trieurs sont t'arriver
        if(++nbAttente == nbMaxAttente){
            attenteTrieurs->release();
        }
        // regarde s'il y a des collègue qui attende dans la fifo
        gestionFifo();
        // attende que le principal
        // qu'il vérifie si tout a été trié
        attentePrincipal->acquire();
        mutex->acquire();
        // recupere la valeur qui indique
        // s'il doivent continuer ou non le trie
        bool tmp = estFini;
        // regarde si tout le monde est venu chercher la valeur
        if(--nbAttente == 0){
            estLiberer = true;
        }
        gestionFifo();
        return tmp;
    }

    /**
     * Attend que tout les trieurs est fini
     * @brief attenteFinTrie
     */
    void attenteFinTrie(){
        attenteTrieurs->acquire();
    }

    /**
     * libere tout les trieurs et indique s'il doivent
     * refaire un trie ou non
     * @brief libereTrie
     * @param fini - indique si on doit refaire un trie
     */
    void libereTrie(bool fini){
        mutex->acquire();
        estFini = fini;
        int i;
        // libere tout le monde
        for(i = 0; i < nbMaxAttente; i++){
            attentePrincipal->release();
        }
        estLiberer = false;
        mutex->release();
    }
};

#endif // MONITEURBUBBLE_H
