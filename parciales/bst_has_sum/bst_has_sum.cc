#include <iostream>

#include "bst.h"
#include "misc.h"

// Ejercicio 1 (parcial 2do cuatrimestre 2019)
// Dado un árbol binario de búsqueda t conteniendo números arbitrarios y un
// número objetivo x, nos interesa saber si existen dos números u,v en t tales
// que u + v = x. Proponer un algoritmo para resolver este problema sujeto a
// las siguientes consideraciones:
//   * Debe correr en tiempo O(n), siendo n la cantidad de nodos del árbol.
//   * Debe tener una complejidad espacial de peor caso constante.
// Nota: puede asumirse que se conoce el padre de cada nodo del árbol.

template<class T>
bool bst_has_sum(const bst<T> &t, const T &x)
{
    const bst<T>
        *i = min_node(&t),
        *j = max_node(&t);

    while(i != j)
    {
        T sum = i->root + j->root;

        if(sum == x)
            return true;
        else if(sum < x)
            i = successor(i);
        else
            j = predecessor(j);        
    }

    return false;
}

template<class T>
const bst<T> *max_node(const bst<T> *t)
{
    const bst<T> *current = t;
    for(; current->right; current = current->right);
    return current;
}

template<class T>
const bst<T> *min_node(const bst<T> *t)
{
    const bst<T> *current = t;
    for(; current->left; current = current->left);
    return current;
}

template<class T>
const bst<T> *successor(const bst<T> *t)
{
    const bst<T> *current = t, *succ = nullptr;

    if(current->right)
        succ = min_node(current->right);
    else
        for(succ = current->up;
            succ->left != current;
            current = succ, succ = current->up);

    return succ;
}

template<class T>
const bst<T> *predecessor(const bst<T> *t)
{
    const bst<T> *current = t, *pred = nullptr;

    if(current->left)
        pred = max_node(current->left);
    else
        for(pred = current->up;
            pred->right != current;
            current = pred, pred = current->up);

    return pred;
}


int main()
{
    // t:
    //           10
    //         /    \
    //        9     20
    //       /     /   \
    //      4     14   21
    //       \    /  \    \
    //        6  12  17   24

    bst<int>
        l6(6), l12(12), l17(17), l24(24),
        n4(4,nullptr,&l6), n9(9,&n4,nullptr),
        n14(14,&l12,&l17), n21(21,nullptr,&l24),
        n20(20,&n14,&n21), t(10,&n9,&n20);

    bool
        has_21 = bst_has_sum(t, 21),
        has_11 = bst_has_sum(t, 11),
        has_26 = bst_has_sum(t, 26),
        has_13 = bst_has_sum(t, 13);

    std::cout
        << "BST "
        << (has_21 ? "has" : "does not have")
        << " two nodes u,v such that u+v = 21"
        << std::endl;

    std::cout
        << "BST "
        << (has_11 ? "has" : "does not have")
        << " two nodes u,v such that u+v = 11"
        << std::endl;

    std::cout
        << "BST "
        << (has_26 ? "has" : "does not have")
        << " two nodes u,v such that u+v = 26"
        << std::endl;

    std::cout
        << "BST "
        << (has_13 ? "has" : "does not have")
        << " two nodes u,v such that u+v = 13"
        << std::endl;

    return 0;
}
