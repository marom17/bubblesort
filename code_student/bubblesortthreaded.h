#ifndef BUBBLESORTTHREADED_H
#define BUBBLESORTTHREADED_H

#include <isort.h>
#include <QDebug>
#include <QThread>

template<typename T>
class BubbleSortThreaded : public ISort<T>, QThread
{
private:
    bool inactivite;
    int indexDebut;
    int indexFin;
    T tableau[];

public:

    BubbleSortThreaded(int indexDebut, int indexFin, T tableau[]) {
        inactivite = false;

        this->indexDebut = indexDebut;
        this->indexFin = indexFin;

        this->tableau = tableau;
    }

    virtual void sort(T a[], qint64 size)
    {
        qDebug() << " Doing nothing :-) ";
    }

    bool getInactivite(){
        return inactivite;
    }
};

#endif // BUBBLESORTTHREADED_H
