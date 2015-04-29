#ifndef BUBBLESORTTHREADED_H
#define BUBBLESORTTHREADED_H

#include <isort.h>
#include <QDebug>

template<typename T>
class BubbleSortThreaded : public ISort<T>
{
private:

public:

    BubbleSortThreaded() {}

    virtual void sort(T a[], qint64 size)
    {
        qDebug() << " Doing nothing :-) ";
    }
};

#endif // BUBBLESORTTHREADED_H
