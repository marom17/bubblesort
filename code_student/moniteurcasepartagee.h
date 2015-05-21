#ifndef MONITEURCASEPARTAGEE_H
#define MONITEURCASEPARTAGEE_H

#include <QMutex>
#include <QWaitCondition>
#include <QSemaphore>

class MoniteurCasePartagee
{
private:
    QSemaphore *mutex;
    QSemaphore *attente;
    bool estAttente;

public:
    MoniteurCasePartagee(){
        mutex = new QSemaphore(1);
        attente = new QSemaphore(0);
        estAttente = false;
    }

    ~MoniteurCasePartagee(){
        delete mutex;
        delete attente;
    }

    void attenteCollegues(){
        mutex->acquire();
        if(estAttente){
            estAttente = false;
            mutex->release();
            attente->release();
        }else{
            estAttente = true;
            mutex->release();
            attente->acquire();
        }
    }
};

#endif // MONITEURCASEPARTAGEE_H
