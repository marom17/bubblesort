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

 Voici les resultat en moyenne pour 10 test avec le même nombre de thread pour un
 tableau de 3361 valeurs avec une graine random de 0:

 1 thread => 22 ms
 2 thread => 3680 ms
 3 thread => 2001 ms
 4 thread => 1394 ms
 5 thread => 1387.6 ms
 6 thread => 1109.5 ms
 7 thread => 1005.4 ms
 8 thread => 883.2 ms

 On a pu remarquer qu'avec des threads, sa ne trier pas forcement plus rapidement
 qu'avec un thread, cela peut-être du au fait que le changement de contexte prennent
 un certain temps et qu'il ralentissent l'algorithme. On remarque que plus il y a
 de thread plus on trie vite, on peut établir que comme la compléxité de l'algorithme
 diminue avec le nombre de thread. Le bubblesort à une compléxite en O(n^2),
 n correspondant à la taille du tableu mais si on divise la taille pour plusieurs
 thread, la compléxité est départagé entre les différents thread et donc on a une
 compléxité qui correspond à O((taille/nbThread)^2).

 Remarque(s) :
 -----------------------------------------------------------------------------------
*/

#include "iostream"
#include "sorttester.h"

using namespace std;

void bancTest(void){
    int tabsize = 3361;
    SortTester tester;
    //permet de testet avec 3361 de 1 à 8 thread
    for(int nb = 1; nb < 9; nb++){
        cout << "Pour " << nb << " thread." << endl;
        for(int i = 0; i < 10; i++){
            tester.test(tabsize,nb);
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    bancTest();
    int tabsize, nbThread;
    string reponse;
    SortTester tester;
    do{
        cout << "Taille du tableau : ";
        cin >> tabsize;
        cout << "Nombre de thread  : ";
        cin >> nbThread;
        tester.test(tabsize,nbThread);
        cout << endl;
        do{
            cout << "Voulez-vous continuer?[oui/non] :";
            cin >> reponse;
        }while(reponse != "oui" && reponse != "non");
    }while(reponse == "oui");
}
