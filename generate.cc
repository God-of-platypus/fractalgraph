#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    int n = 7; // Valeur de n
    int k = 3; // Valeur de k
    int N = 10; // Nombre de paires à générer

    // Initialiser le générateur de nombres aléatoires
    srand(time(0));

    // Créer N paires aléatoires
    for (int i = 0; i < N; i++)
    {
        int a = rand() % n; // Générer a entre 0 et n-1
        int b = rand() % (k + 1); // Générer b entre 0 et k

        // Afficher la paire sous la forme "{a, b}"
        cout << "{" << a << ", " << b << "}" << endl;
    }

    return 0;
}
