#include <algorithm>
#include "utils.h"
#include "zeros.h"

using namespace std;


// Primera solución, por fuerza bruta: evalúa las Θ(n³) ternas de índices
// distintos de A, siendo n la cantidad total de valores en dicho arreglo. La
// complejidad temporal resultante es cúbica.
bool has_zero_sum_elems_1(std::vector<int> &A)
{
    size_t n = A.size();

    for(size_t i = 0; i < n; ++i)
        for(size_t j = i+1; j < n; ++j)
            for(size_t k = j+1; k < n; ++k)
                if(A[i]+A[j]+A[k] == 0)
                    return true;

    return false;
}

// Segunda solución: ordenando primero a A, es posible evaluar todos los pares
// de índices de números negativos (i, j) y, por cada uno de ellos, decidir 
// eficientemente si -(A[i]+A[j]) está entre los valores positivos, repitiendo
// esta misma idea en el sentido inverso si ningún par lo satisface. Al evaluar
// O(n²) pares, realizando trabajo O(log n) para cada uno, la complejidad
// temporal asintótica resultante es O(n² log n).
bool has_zero_sum_elems_2(std::vector<int> &A)
{
    size_t n = A.size();
    // El intervalo [first_neg, last_neg) encierra los valores negativos.
    size_t first_neg = 0, last_neg;
    // De la misma forma, [first_pos, last_pos) encierra los positivos.
    size_t first_pos, last_pos = n;

    // Primer paso: ordenar A (asumimos complejidad O(n log n), aunque el sort
    // de la STL garantiza esta complejidad en caso promedio al implementar
    // Quicksort).
    std::sort(A.begin(), A.end());

    indices(A, &last_neg, &first_pos);

    // Casos simples:
    // i. A contiene únicamente números negativos o bien positivos.
    if(last_neg == n || first_pos == 0)
        return false;
    // ii. A contiene tres o más ceros.
    if(first_pos - last_neg >= 3)
        return true;

    // Barremos todos los pares de índices de números negativos y comprobamos
    // si el número restante aparece entre los positivos.
    for(size_t i = first_neg; i < last_neg; ++i)
        for(size_t j = i+1; j < last_neg; ++j)
            if(bsearch(A, -A[i]-A[j], first_pos, last_pos))
                return true;

    // Ídem anterior invirtiendo los signos.
    for(size_t i = first_pos; i < last_pos; ++i)
        for(size_t j = i+1; j < last_pos; ++j)
            if(bsearch(A, -A[i]-A[j], first_neg, last_neg))
                return true;

    // En última instancia, si A contiene uno o dos ceros, comprobamos si
    // alguno de los negativos aparece negado entre los positivos.
    if(first_pos - last_neg > 0)
        for(size_t i = first_neg; i < last_neg; ++i)
            if(bsearch(A, -A[i], first_pos, last_pos))
                return true;

    return false;
}

// Tercera y última variante: una sofisticación de la segunda estrategia en la
// que utilizamos la solución de un subproblema auxiliar que consiste en
// decidir si un arreglo ordenado contiene dos números cuya suma sea un valor
// dado arbitrario. Al poder resolver este subproblema en tiempo lineal, 
// la complejidad total resultante termina siendo O(n²).
bool has_zero_sum_elems_3(std::vector<int> &A)
{
    size_t n = A.size();
    // El intervalo [first_neg, last_neg) encierra los valores negativos.
    size_t first_neg = 0, last_neg;
    // De la misma forma, [first_pos, last_pos) encierra los positivos.
    size_t first_pos, last_pos = n;

    // Primer paso: ordenar A (asumimos complejidad O(n log n), aunque el sort
    // de la STL garantiza esta complejidad en caso promedio al implementar
    // Quicksort).
    std::sort(A.begin(), A.end());

    indices(A, &last_neg, &first_pos);

    // Casos simples:
    // i. A contiene únicamente números negativos o bien positivos.
    if(last_neg == n || first_pos == 0)
        return false;
    // ii. A contiene tres o más ceros.
    if(first_pos - last_neg >= 3)
        return true;

    // Para cada negativo A[i], comprobamos si existen dos números positivos
    // cuya suma negada sea A[i].
    for(size_t i = first_neg; i < last_neg; ++i)
        if(has_two_k_sum_elems(A, -A[i], first_pos, last_pos))
            return true;

    // Ídem anterior invirtiendo los signos.
    for(size_t i = first_pos; i < last_pos; ++i)
        if(has_two_k_sum_elems(A, -A[i], first_neg, last_neg))
            return true;

    // En última instancia, si A contiene uno o dos ceros, comprobamos si
    // alguno de los negativos aparece negado entre los positivos.
    if(first_pos - last_neg > 0)
        for(size_t i = first_neg; i < last_neg; ++i)
            if(bsearch(A, -A[i], first_pos, last_pos))
                return true;

    return false;
}

bool has_zero_sum_elems(std::vector<int> &A)
{
    return has_zero_sum_elems_3(A);
}
