#include "utils.h"


// Función auxiliar para computar el límite superior del intervalo de números
// negativos y el límite inferior del intervalo de positivos en el arreglo
// ordenado A.
void indices(
    const std::vector<int> &A,
    size_t *last_neg,
    size_t *first_pos)
{
    // Buscamos primero la primera ocurrencia del cero en A, o la posición
    // donde debería aparecer el cero en su defecto.
    size_t zero_idx;
    bool found = bsearch(A, 0, 0, -1, &zero_idx);

    // Independientemente del resultado, el índice computado más arriba
    // es el límite superior del intervalo de negativos.
    *last_neg = zero_idx;

    if(!found)
        // Cuando el cero no está, el índice computado se corresponde al primer
        // valor positivo en el arreglo.
        *first_pos = zero_idx;
    else
        // Si el cero está, buscamos la primera ocurrencia del entero positivo
        // más chico (1) desde el índice del cero en adelante.
        bsearch(A, 1, zero_idx, -1, first_pos);
}

// Solución en tiempo lineal al subproblema auxiliar de decidir si en el
// arreglo ordenado A existen dos valores cuya suma sea k en el intervalo
// [from, to).
bool has_two_k_sum_elems(
    const std::vector<int> &A,
    int k,
    size_t from,
    ssize_t to)
{
    to = (to == -1 || to >= A.size()) ? A.size() : to;
    size_t i = from, j = to-1;
    int m;

    while(i < j)
    {
        m = A[i]+A[j];
        if(m == k)
            return true;
        if(m > k)
            j--;
        else
            i++;
    }

    return false;
}
