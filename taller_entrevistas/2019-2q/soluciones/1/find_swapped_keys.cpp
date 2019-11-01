#include "find_swapped_keys.h"


// Primera solución:
//   1. Calcular el recorrido inorder del árbol.
//   2. Buscar secuencialmente en el recorrido claves consecutivas que no
//      estén en orden creciente. 
// Este algoritmo se apoya en la propiedad de que el recorrido inorder de
// cualquier árbol binario de búsqueda está ordenado crecientemente.
// La complejidad temporal es O(n) (siendo n la cantidad de nodos del árbol).
// De este modo, logramos un algoritmo asintóticamente óptimo puesto que 
// necesariamente debemos visitar cada nodo del árbol.
// Por otro lado, la complejidad espacial también es lineal (como consecuencia
// de la recursividad de inorder y del volcado del recorrido en una lista
// auxiliar).
void find_swapped_keys_1(bst *t, int &k1, int &k2)
{
    std::list<int> in;
    inorder(t, in);

    auto it2 = in.begin(), it1 = it2++;

    while(it2 != in.end() && *it1 < *it2)
        it1++, it2++;

    k1 = *it1++;
    k2 = *it2++; 

    while(it2 != in.end() && *it1 < *it2)
        it1++, it2++;

    if(it2 != in.end())
        k2 = *it2;
}

// Función auxiliar para calcular el recorrido inorder del árbol binario
// pasado como argumento.
void inorder(const bst *t, std::list<int> &in)
{
    if(t->left)
        inorder(t->left, in);

    in.push_back(t->root);

    if(t->right)
        inorder(t->right, in);
}

// Esta segunda variante parte de la misma idea subyacente aunque optimiza el
// uso de memoria. Por un lado, el recorrido inorder se calcula iterativamente
// (mediante el algoritmo de Morris [1]). Además de esto, la búsqueda de las
// claves en desorden se realiza de forma embebida durante el cómputo del
// recorrido. De este modo, la complejidad espacial resulta constante. Sin
// embargo, el algoritmo requiere modificar transitoriamente el árbol a medida
// que se recorre. En situaciones donde esto no fuera posible, esta solución
// quedaría descartada.
// [1] https://doi.org/10.1016%2F0167-6423%2888%2990063-9
void find_swapped_keys_2(bst *t, int &k1, int &k2)
{
    bst *current = t, *prev, *next;
    bool first_found = false;
 
    while(current)
        if(current->left == nullptr)
        {
            next = current->right;

            if(next && current->root > next->root)
                k1 = first_found ? k1 : current->root,
                k2 = next->root,
                first_found = true;

            current = next;
        }
        else
        {
            prev = current->left;
            while(prev->right && prev->right != current)
                prev = prev->right;

            if(prev->right == current)
            {
                prev->right = nullptr;
                next = current->right;

                if(next && current->root > next->root)
                    k1 = first_found ? k1 : current->root,
                    k2 = next->root,
                    first_found = true;

                current = next;
            }
            else
            {
                prev->right = current;
                current = current->left;
            }
        }
}

void find_swapped_keys(bst *t, int &k1, int &k2)
{
    find_swapped_keys_2(t, k1, k2);
}


