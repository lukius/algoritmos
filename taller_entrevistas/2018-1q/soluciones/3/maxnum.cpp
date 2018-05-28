// Tercer problema: computar el número más grande posible de k dígitos que
// puede formarse con los dígitos de dos arreglos distintos, respetando el
// orden relativo de los dígitos en cada uno de ellos.

#include <algorithm>
#include <limits>

#include "maxnum.h"

using namespace std;


template<class T>
using matrix2 = vector<vector<T>>;
template<class T>
using matrix3 = vector<matrix2<T>>;


// Exploramos una única solución basada en la técnica algorítmica de
// programación dinámica. Para ello, introducimos la función N(i, j, d) para
// representar el número más grande posible de d dígitos considerando los
// dígitos de A[0..n-1] comprendidos desde el índice i en adelante y los
// dígitos de B[0..m-1] desde el índice j en adelante. Vimos entonces que
// * N(i, j, 0) = 0  (i ≥ 0; j ≥ 0)
// * N(i, j, d) = -∞ (1 ≤ d ≤ k; i ≥ n; j ≥ m)
// * N(i, j, d) = máx {
//                      N(i+1, j,   d-1) + 10^(d-1) * A[i],
//                      N(i,   j+1, d-1) + 10^(d-1) * B[j],
//                      N(i+1, j,   d),
//                      N(i,   j+1, d)
//                    } (en cualquier otro caso, con 1 ≤ d ≤ k)
// y que, por ende, el valor buscado es N(0, 0, k).
// El algoritmo consiste en tabular N computando los valores en un sentido
// adecuado definido por las relaciones matemáticas de más arriba. La 
// complejidad temporal resultante es O(nmk).
// NOTA: por las limitaciones de los enteros de precisión finita, esta 
// implementación podría arrojar valores incorrectos cuando k es
// suficientemente grande. No obstante, el objetivo es ilustrar los conceptos
// algorítmicos involucrados en el problema.
int max_number(
    const vector<int> &A,
    const vector<int> &B,
    size_t k)
{
    size_t n = A.size();
    size_t m = B.size();

    matrix3<int> N;
    matrix2<size_t> pows;

    int ninf = numeric_limits<int>::min();
    size_t pow = 1;
    int n1, n2, n3, n4;

    // Tabulamos también las potencias de 10 multiplicadas por cada dígito para
    // no requerir calcularlas cada vez que las necesitemos a medida que
    // completamos la tabla de N. De esta forma, pows[d][i] representará el 
    // valor i * 10^d.
    for(size_t d = 0; d <= k; d++)
    {
        pows.push_back(vector<size_t>());
        for(size_t i = 0; i <= 9; i++)
            pows[d].push_back(i*pow);
        pow *= 10;
    }

    for(size_t i = 0; i <= n; i++)
    {
        N.push_back(matrix2<int>());
        for(size_t j = 0; j <= m; j++)
        {
            N[i].push_back(vector<int>());
            for(size_t d = 0; d <= k; d++) 
                N[i][j].push_back(d == 0 ? 0 : ninf);
        }
    }

    for(ssize_t i = n; i >= 0; i--)
    {
        for(ssize_t j = m; j >= 0; j--)
        {
            for(size_t d = 1; d <= k; d++)
            {
                n1 = n2 = n3 = n4 = ninf;

                if(i < n)
                {
                    n1 = N[i+1][j][d-1] + pows[d-1][A[i]];
                    n3 = N[i+1][j][d];
                }

                if(j < m)
                {
                    n2 = N[i][j+1][d-1] + pows[d-1][B[j]];
                    n4 = N[i][j+1][d];
                }

                N[i][j][d] = max({n1, n2, n3, n4});
            }
        }
    }

    return N[0][0][k];
}
