#include "sorttester.h"
#include <time.h>
#include <iostream>
#include <QtMath>
#include <QVector>
#include <QThread>

#include "bubblesort.h"
#include "bubblesortthreaded.h"
#include "time.h"
#include "sortthread.h"

void SortThread::threadSort(){
    while(!moniteurControl->attenteVerification()){
        inactivite = true;
        // vérifie si ce n'est pas le premier thread
        if(moniteurDebut != nullptr){
            sort(tableau+indexDebut+1, indexFin-indexDebut);
            // attend que son premier collegue finisse de trier
            moniteurDebut->attenteCollegues();
            // si la case commune est plus grande que ca suivante, swap les valeurs
            if(tableau[indexDebut] > tableau[indexDebut+1]){
                tableau[indexDebut]   = tableau[indexDebut] ^ tableau[indexDebut+1];
                tableau[indexDebut+1] = tableau[indexDebut] ^ tableau[indexDebut+1];
                tableau[indexDebut]   = tableau[indexDebut] ^ tableau[indexDebut+1];
                // indique qu'il y a eu un swap
                inactivite = false;
            }
        }
        else{
            sort(tableau+indexDebut, indexFin-indexDebut);
        }

        // verifie si ce n'est pas le dernier thread
        if(moniteurFin != nullptr){
            // attend son second collegue finisse de trier
            moniteurFin->attenteCollegues();
        }
    }
}
