#ifndef MONITEURBUBBLE_H
#define MONITEURBUBBLE_H

#include <QMutex>
#include <QWaitCondition>

class MoniteurBubble
{
private:
    QMutex mutex();
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

    bool attentePrincipal(){
        mutex.lock();
        if(nbAttente >= nbMaxAttente){
            principal.wakeAll();
        }
        trieur.wait(&mutex);
        mutex.unlock();
        return estFini;
    }

    void attenteTrie(){
        mutex.lock();
        if(nbAttente < nbMaxAttente){
            principal.wait(&mutex);
        }
        mutex.unlock();
    }

    void libereTrie(bool fini){
        mutex.lock();
        estFini = fini;
        trieur.wakeAll();
        mutex.unlock();
    }

    void libereTrie(){
        libereTrie(estFini);
    }
};

#endif // MONITEURBUBBLE_H
