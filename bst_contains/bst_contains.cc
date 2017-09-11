#include <iostream>
#include <vector>
using namespace std;


// Dado el recorrido preoder P[i..j] de un árbol binario de búsqueda, la
// siguiente función computa el índice en P en el que comienza el recorrido
// preorder del subárbol derecho.
template<class T>
ssize_t subtree_limit(const vector<T> &P, ssize_t i, ssize_t j)
{
    ssize_t mid;
    // La raíz del árbol viene dada por el índice i.
    const T &r = P[i];
    i++;    

    // Caso 1: subárbol derecho vacío.
    if(P[j] < r)
        return j+1;

    // Caso 2: subárbol izquierdo vacío.
    if(i >= j || P[i] > r)
        return i;

    // Caso 3: hay al menos un elemento en cada subárbol.
    // En lo que sigue, tenemos como invariante que P[i] < r y P[j] > r. Por
    // ende, debemos cortar cuando i y j sean índices contiguos y devolver el
    // valor de j en ese momento.
    while(i != j-1)
    {
        mid = (i + j) / 2;
        if(P[mid] > r)
            j = mid;
        if(P[mid] < r)
            i = mid;
    }

    return j;
}

// Determina si e está presente en el árbol binario de búsqueda cuyo recorrido
// preorder viene dado por P. Los índices i y j engloban la porción del arreglo
// que contiene el recorrido preorder del abb actual (P[i..j-1]).

// Nota: como vimos en clase, la complejidad temporal cuando el árbol
// subyacente a P es AVL es O(log^2 n), siendo n la cantidad de nodos del
// árbol. No obstante, esta estrategia funciona para cualquier abb. Pensar
// entonces cuál será la complejidad en el caso general.
template<class T>
bool tree_contains(const vector<T> &P, const T &e,
                   ssize_t i = 0, ssize_t j = -1)
{
    // En la invocación original, j toma el valor por defecto de -1. Lo
    // siguiente ajusta entonces el valor inicial de j.
    if(j == -1)
        j = P.size();

    // Árbol vacío: no contiene ningún elemento.
    if(i >= j)
        return false;

    bool contained = true;
    // La raíz del árbol viene dada por el índice i.
    const T &r = P[i];

    if(r != e)
    {
        // Determinamos el índice en P donde arranca el recorrido preorder del
        // subárbol derecho.
        ssize_t k = subtree_limit(P, i, j-1);
        if(r > e)
            // Por tratarse de un abb, debemos continuar la búsqueda en el
            // subárbol izquierdo al tener que e < r.
            contained = tree_contains(P, e, i+1, k);
        else
            // En otro caso, debemos buscar en el subárbol derecho.
            contained = tree_contains(P, e, k, j);
    }

    return contained;
}


int main(int argc, char *argv[])
{
    /*
                     20
             10              30
        5         15             35
               12    17       32

    */
    vector<int> P{20,10,5,15,12,17,30,35,32};
    int e;

    e = 32;
    cout << e;
    if(!tree_contains(P,e))
        cout << " no";
    cout << " está." << endl;

    e = 200;
    cout << e;
    if(!tree_contains(P,e))
        cout << " no";
    cout << " está." << endl;

    e = -1;
    cout << e;
    if(!tree_contains(P,e))
        cout << " no";
    cout << " está." << endl;

    return 0;
}
