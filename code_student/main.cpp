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
la second case s'il n'est pas premier jusqu'à la seconde case commune avec l'autre

 Remarque(s) :
 -----------------------------------------------------------------------------------
*/

#include "iostream"
#include "sorttester.h"

using namespace std;

int main(int argc, char *argv[])
{
    while(1){
    int tabsize, nbThread;
    cout << "Taille du tableau : ";
    cin >> tabsize;
    cout << "Nombre de thread  : ";
    cin >> nbThread;
    SortTester tester;
    tester.test(tabsize,nbThread);
    }
}
