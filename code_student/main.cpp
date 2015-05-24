/*
 -----------------------------------------------------------------------------------
 Fichier     : main.cpp
 Auteur(s)   : Domingues Pedrosa João Miguel & Maillard Romain
 Date        : 10.05.2015

 Introduction:
 Le but de ce laboratoire est de séparer les tris en différents thread et d'ainsi
 observer les différents complexité pour synchroniser plusieurs tâche.

 Solution:
 Nous somme partie que chaque thread avait une ou deux voisins (qu'il partage une ou
 deux case en commun). De ce fait, à la fin de son trie, le thread doit attendre que son
 voisin termine, pour pouvoir échanger la valeur sur la case commune avec la première
 de c'est valeurs. Pour pouvoir faire ceci, un thread va trie sa partie qui correspond de
 la second case s'il n'est pas premier jusqu'à la seconde case commune qui est incluse.
 Ensuite une fois tout ceci fait, on attend au rendez-vous centreal (MoniteurBubble)
 que tout le monde se rejoigne. Après, le controleur de thread (BubbleSortThreaded)
 regarde s'il n'y a pas eu de swap et si oui, il redemande au thread de refaire un
 trie, sinon il demande à tout le monde de s'arrêter.

 La repartition des cases dans le threads est très simple. On regarde d'abord si
 le nombre de thread n'execede pas la taille du tableau, si oui, on dit que le nombre
 de thread est égal à la taille. Ensuite, on divise la taille par le nombre de thread
 pour avoir la taille de chaque tableau passer, on voit s'il y a des restes pour ajouter
 un de plus au premiers.

 On a pu remarquer qu'avec des threads, sa ne trier pas forcement plus rapidement
 cela peut-être du au changement de contexte qui prennent quand même du temps à
 s'executer.


 Remarque(s) :
 -----------------------------------------------------------------------------------
*/

#include "iostream"
#include "sorttester.h"

using namespace std;

int main(int argc, char *argv[])
{
    int tabsize, nbThread;
    tabsize =3361;
    nbThread = 2;
    SortTester tester;
    for(int nb = nbThread; nb < 9; nb++){
        cout << "Pour " << nbThread << " thread." << endl;
        for(int i = 0; i < 10; i++){
            tester.test(tabsize,nb);
        }
//        cout << "Taille du tableau : ";
//        cin >> tabsize;
//        cout << "Nombre de thread  : ";
//        cin >> nbThread;
//        SortTester tester;
        cout << endl;
    }
}
