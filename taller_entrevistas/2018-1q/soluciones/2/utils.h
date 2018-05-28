#ifndef _UTILS_H_
#define _UTILS_H_

#include <unistd.h>
#include <vector>


// Búsqueda binaria de elem en el intervalo delimitado por [from, to) dentro
// del arreglo ordenado A. Cuando idx es un puntero no nulo, su valor al final
// de la ejecución contendrá el índice de la primera ocurrencia de elem en el
// rango especificado o bien el índice de la posición donde debería aparecer
// elem, dependiendo del resultado de la búsqueda.
template<class T>
bool bsearch(
    const std::vector<T> &A,
    const T &elem,
    size_t from =0,
    ssize_t to =-1,
    size_t *idx =nullptr)
{
    to = (to == -1 || to > A.size()) ? A.size() : to;
    size_t i = from, j = to, m;
    bool found = false;

    while(i < j)
    {
        m = i + (j-i)/2;

        if(A[m] == elem && (m == 0 || A[m-1] != elem))
        {
            i = m;
            found = true;
            break;
        }
        else if(A[m] >= elem)
            j = m;
        else // A[m] < elem
            i = m+1;
    }

    if(idx)
        *idx = i;

    return found;
}

void indices(const std::vector<int>&, size_t*, size_t*);
bool has_two_k_sum_elems(const std::vector<int>&, int, size_t =0, ssize_t =-1);

#endif
