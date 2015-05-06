#ifndef MONITEURCASEPARTAGEE_H
#define MONITEURCASEPARTAGEE_H

#include <QMutex>
#include <QWaitCondition>

class MoniteurCasePartagee
{
private:
    QMutex mutex;
    QWaitCondition attente;
    int nbMaxAttente;
    int nbAttente;

public:
    MoniteurCasePartagee(int nbMaxAttente){
        this->nbMaxAttente = nbMaxAttente;
        nbAttente = 0;
    }

    ~MoniteurCasePartagee();

    void attenteCollegues(){
        mutex.lock();
        if(++nbAttente >= nbMaxAttente){
            attente.wait();
        }else{
            attente.wakeAll();
        }
        mutex.unlock();
    }
};

#endif // MONITEURCASEPARTAGEE_H
