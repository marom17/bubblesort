#ifndef MONITEURBUBBLE_H
#define MONITEURBUBBLE_H

#include <QMutex>
#include <QWaitCondition>

class MoniteurBubble
{
private:
    QMutex mutex;
    QWaitCondition trieur;
    QWaitCondition principal;
    int nbMaxAttente;
    int nbAttente;
    bool estFini;

public:
    MoniteurBubble(nbMaxAttente){
        this->nbMaxAttente = nbMaxAttente;
        nbAttente = 0;
        estFini = false;
    }

    ~MoniteurBubble();

    bool attenteTrie(){
        if(nbAttente < nbMaxAttente){
            trieur.wait();
        }else{
            principal.wakeAll();
        }
        return estFini;
    }

    void libereTrie(){
        if(nbAttente < nbMaxAttente){
            principal.wait();
        }else{
            trie.wakeAll();
        }
    }
};

#endif // MONITEURBUBBLE_H
