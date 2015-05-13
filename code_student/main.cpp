
#include "iostream"
#include "sorttester.h"

using namespace std;

int main(int argc, char *argv[])
{
    int tabsize, nbThread;
    cout << "Taille du tableau : ";
    cin >> tabsize;
    cout << "Nombre de thread  : ";
    cin >> nbThread;
    SortTester tester;
    tester.test(tabsize,nbThread);
}
