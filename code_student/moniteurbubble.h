#ifndef MONITEURBUBBLE_H
#define MONITEURBUBBLE_H

#include <QMutex>
#include <QWaitCondition>

class MoniteurBubble
{
private:
    QMutex mutex;
    QWaitCondition attentePrincipal;
    QWaitCondition attenteTrieurs;
    int nbMaxAttente;
    int nbAttente;
    bool estFini;

public:
    MoniteurBubble(int nbMaxAttente){
        this->nbMaxAttente = nbMaxAttente;
        nbAttente = 0;
        estFini = false;
    }

    ~MoniteurBubble();

    bool attenteVerification(){
        mutex.lock();
        if(++nbAttente >= nbMaxAttente){
            attenteTrieurs.wakeAll();
        }
        attentePrincipal.wait(&mutex);
        mutex.unlock();
        return estFini;
    }

    void attenteFinTrie(){
        mutex.lock();
        if(nbAttente < nbMaxAttente){
            attenteTrieurs.wait(&mutex);
        }
        mutex.unlock();
    }

    void libereTrie(bool fini){
        mutex.lock();
        estFini = fini;
        attentePrincipal.wakeAll();
        mutex.unlock();
    }

    void libereTrie(){
        libereTrie(estFini);
    }
};

#endif // MONITEURBUBBLE_H
