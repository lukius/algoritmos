#include <iostream>
#include <vector>

using namespace std;

// Recordatorio del problema:
// Decimos que un arbol binario t es un árbol delta si:
//  * t es un árbol binario de búsqueda,
//  * La diferencia en la cantidad de nodos entre los subárboles de t es a lo
//    sumo 1, y
//  * Ambos subárboles de t son a su vez árboles delta.
// Mostrar que es posible ordenar el recorrido preorder de un árbol delta de n
// nodos en tiempo O(n) sin necesidad de reconstruir el árbol.
// Más abajo se exploran dos posibles soluciones para este problema.


// Dado el recorrido preorder A[i..j-1] de un árbol delta arbitrario, esta
// función computa en tiempo constante la cantidad de nodos del subárbol
// izquierdo.
template<class T>
ssize_t left_subtree_size(const vector<T> &A, ssize_t i, ssize_t j)
{
    ssize_t n = j-i;
    ssize_t n_2 = n/2;
    ssize_t m = i + n_2;
    const T &r = A[i];

    if(n <= 1)
        return 0;

    if(n == 2 && A[i] < A[i+1])
        return 0;
    else if(n == 2)
        return 1;

    if(A[m] < r && A[m+1] > r)
        return n_2;

    if(A[m] < r)
        return n_2 + 1;

    return n_2 - 1;
}

// Dado el recorrido preorder A[i0..j0-1] de un árbol delta arbitrario, este
// algoritmo ordena el recorrido dentro de un arreglo auxiliar B cuyo rango
// útil se delimita por [i1, j1). En definitiva, si notamos k al tamaño del
// subárbol izquierdo de nuestro árbol original, este algoritmo llevará a cabo
// las siguientes tareas:
//   * Ordenará recursivamente A[i0+1..i0+k], que engloba el recorrido preorder
//     del subárbol izquierdo, dentro de B[i1..i1+k-1],
//   * Ordenará recursivamente A[i0+k+1..j0-1], que engloba el recorrido
//     preorder del subárbol derecho, dentro de B[i1+k+1..j1-1], y
//   * Copiará A[i0], la raíz del árbol, a B[i1+k].
// De esto se desprende que la recurrencia T que caracteriza el tiempo de
// ejecución de peor caso del algoritmo viene dada por
//     T(n) = 2T(n/2) + O(1)
// siendo n la cantidad de nodos del árbol (observar que el hecho de ser árbol
// delta nos garantiza que el tamaño de cualquiera de los dos subárboles es
// (n-1)/2 o bien (n-1)/2 +/- 1). Como ya sabemos, esta recurrencia resuelve a
// Theta(n), de manera que la complejidad temporal de este algoritmo resulta
// lineal como se pretendía inicialmente. Por otra parte, al utilizar un arreglo
// auxiliar, su complejidad espacial es también lineal en la cantidad de nodos.
template<class T>
void sort_preorder_into(
    const vector<T> &A, vector<T> &B,
    ssize_t i0=0, ssize_t j0=-1,
    ssize_t i1=0, ssize_t j1=-1)
{
    if(j0 == -1)
    {
        j0 = A.size();
        j1 = A.size();
    }

    if(j0 > i0)
    {
        ssize_t k = left_subtree_size(A, i0, j0);

        sort_preorder_into(A, B, i0+1,   i0+1+k, i1,     i1+k);
        sort_preorder_into(A, B, i0+1+k, j0,     i1+k+1, j1);

        B[i1+k] = A[i0];
    }
}

template<class T>
vector<T> sort_preorder(const vector<T> &A)
{
    vector<T> sorted(A.size());
    sort_preorder_into(A, sorted);
    return sorted; 
}

// El siguiente algoritmo surge con el objeto de optimizar la complejidad
// espacial de la estrategia anterior. La idea, entonces, es desprenderse del
// arreglo auxiliar B de manera de realizar el ordenamiento del recorrido
// directamente sobre el mismo A (i.e., in-place). Para ello, se introduce una
// nueva variable l que indica dónde debe comenzar a copiarse el recorrido
// ordenado. Cuando l = -1, interpretamos que no es necesario desplazar la
// copia: la misma se inicia desde el índice i. Si, por otro lado, l >= 0,
// la copia debe arrancar desde el índice l. En otras palabras, el algoritmo
// procederá de la siguiente manera, siendo A[i..j-1] el recorrido preorder a
// ordenar y k el tamaño del subárbol izquierdo:
//  * Si l = -1:
//    * Guardar A[i], la raíz del árbol, en r.
//    * Ordenar recursivamente A[i+1..i+k] (el recorrido del subárbol
//      izquierdo) con l = i (esto es, corremos a la izquierda los valores
//      correspondientes al subárbol izquierdo dado que la raíz es mayor que
//      todos ellos).
//    * Ordenar recursivamente A[i+k+1..j-1] (el recorrido del subárbol
//      derecho) con l = -1 (puesto que no es necesario desplazarlo siendo
//      que sus valores son mayores que la raíz y que los del otro subárbol).
//    * Copiar la raíz del árbol, r, a A[i+k].
//
//  * Si l >= 0:
//    * Guardar A[i], la raíz del árbol, en r.
//    * Ordenar recursivamente A[i+1..i+k] (el recorrido del subárbol
//      izquierdo) con l = l (es decir, respetando el valor de l que vino como
//      argumento).
//    * Ordenar recursivamente A[i+k+1..j-1] (el recorrido del subárbol
//      derecho) con l = l+k+1 (es decir, tomando como base el valor de l
//      pasado como argumento y salteando el subárbol izquierdo y la raíz).
//    * Copiar la raíz del árbol, r, a A[l+k].
//
// Es evidente, entonces, que la complejidad temporal sigue siendo lineal en n,
// la cantidad de nodos del árbol. No obstante, la complejidad espacial es
// ahora O(log n) puesto que ya no es necesario utilizar ninguna estructura
// adicional.
template<class T>
void sort_preorder_in_place(
    vector<T> &A,
    ssize_t i=0, ssize_t j=-1,
    ssize_t l=-1)
{
    if(j == -1)
        j = A.size();

    T r = A[i];

    if(j > i)
    {
        ssize_t k = left_subtree_size(A, i, j);

        sort_preorder_in_place(A, i+1,   i+1+k,  l == -1 ?  i : l);
        sort_preorder_in_place(A, i+1+k, j,      l == -1 ? -1 : l+k+1);

        A[l == -1 ? i+k : l+k] = r;
    }
}

int main(int argc, char *argv[])
{
    /*
                     7
              3             12
         1        6     10     15
               5          
    */
    
    cout << "A = 7 3 1 6 5 12 10 15" << endl;
    vector<int> A {7, 3, 1, 6, 5, 12, 10, 15};

    cout << "sort_preorder(A)          =";
    vector<int> B = sort_preorder(A);
    for(auto elem: B)
        cout << " " << elem;

    cout << endl << "sort_preorder_in_place(A) =";
    sort_preorder_in_place(A);
    for(auto elem: A)
        cout << " " << elem;

    cout << endl;

    return 0;
}
