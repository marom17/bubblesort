//#include "sorttester.h"
//#include <time.h>
//#include <iostream>
//#include <QtMath>
//#include <QVector>
//#include <QThread>

//#include "bubblesort.h"
//#include "bubblesortthreaded.h"
//#include "time.h"
//#include "sortthread.h"

//template<typename T>
//void SortThread<T>::threadSort(){
//    while(!moniteurControl->attenteVerification()){
//        inactivite = true;
//        // vérifie si ce n'est pas le premier thread
//        if(debut != nullptr){
//            sort(tableau+1, taille);
//            // attend que son premier collegue finisse de trier
//            debut->acquire();
//            // si la case commune est plus grande que ca suivante, swap les valeurs
//            if(tableau[0] > tableau[1]){
//                tableau[0] = tableau[0] ^ tableau[1];
//                tableau[1] = tableau[0] ^ tableau[1];
//                tableau[0] = tableau[0] ^ tableau[1];
//                // indique qu'il y a eu un swap
//                inactivite = false;
//            }
//        }
//        else{
//            sort(tableau, taille);
//        }

//        // verifie si ce n'est pas le dernier thread
//        if(fin != nullptr){
//            //libere le second collegue
//            fin->release();
//        }
//    }
//}

//template<typename T>
//SortThread<T>::SortThread(T tableau[], qint64 taille, MoniteurBubble *moniteurControl): QThread(){

//    inactivite = true;

//    this->taille = taille;

//    this->tableau = tableau;

//    this->moniteurControl = moniteurControl;
//    this->debut = nullptr;
//    this->fin   = nullptr;

//}

//template<typename T>
//void SortThread<T>::setDebut(QSemaphore *debut){
//    this->debut = debut;
//}

//template<typename T>
//void SortThread<T>::setFin(QSemaphore *fin){
//    this->fin = fin;
//}

//template<typename T>
//void SortThread<T>::sort(T a[], qint64 size){
//    for (int c = size - 1 ; c > 0; --c){
//        for (int d = 0 ; d < c; ++d){
//            if (tableau[d] > tableau[d+1]){
//                tableau[d]   = tableau[d] ^ tableau[d+1];
//                tableau[d+1] = tableau[d] ^ tableau[d+1];
//                tableau[d]   = tableau[d] ^ tableau[d+1];
//            }
//        }
//    }
//}

//template<typename T>
//bool SortThread<T>::getInactivite(){
//    return inactivite;
//}
