// Primer problema: ordenar un arreglo numérico a través de un criterio que 
// consiste en considerar primero la cantidad de unos en la representación
// binaria de los números, desempatando por el valor númerico en caso de 
// igualdad.

#include <vector>
#include <unistd.h>
#include <math.h>

#include "ones.h"

using namespace std;


// Función auxiliar para computar la cantidad de unos en la representación
// binaria del entero positivo a. Utilizamos operaciones de bits, aunque
// otra forma posible de hacerlo es con aritmética (división entera por dos en
// lugar de shift a derecha y resto en la división por dos en lugar del and
// para proyectar el valor del bit menos significativo).
int ones(int a)
{
    int count = 0;
    while(a)
    {
        if(a & 1)
            count++;
        a >>= 1;
    }

    return count;
};


// Relación de orden para la primera solución estudiada: cada comparación entre
// dos enteros a y b se resuelve evaluando la cantidad de unos en ambas
// representaciones binarias, iterando bit por bit en cada caso.
struct Relation1
{
    bool operator()(int a, int b) const
    {
        int ones_a = ones(a);
        int ones_b = ones(b);

        return ones_a < ones_b || (ones_a == ones_b && a < b);
    };
};


// Relación de orden para la segunda solución estudiada: dados a y b, la
// comparación se resuelve iterando de a k bits para computar la cantidad de
// unos. Para esto, precomputamos la cantidad de unos en todos los números
// de k bits (i.e., 0,1,...,2^k - 1) y tabulamos esta información. El valor
// óptimo de k lo calculamos estimando la cantidad de operaciones de cada
// estrategia:
// * Usando la relación de más arriba, tenemos n log₂ n log₂ m operaciones
//   en total, siendo n la cantidad de valores a ordenar y m el valor máximo
//   permitido para dichos valores.
// * Usando ésta, tenemos n log₂ n (log₂ m)/k + k2^k operaciones, donde el
//   segundo término representa el trabajo para precomputar la cantidad de unos
//   de cada entero de k bits.
// En definitiva, el objetivo es encontrar el valor de k más conveniente tal
// que n log₂ n (log₂ m)/k + k2^k ≤ n log₂ n log₂ m. Con un script sencillo
// puede verse que, tomando las restricciones dadas en el problema
// (n ≤ 10^5 y m ≤ 10^9), el valor óptimo de k es 14.   
struct Relation2
{
    vector<int> v_ones;
    int mask, k;

    Relation2(int _k) : k(_k)
    {
        int l = pow(2,k);
        v_ones.resize(l);

        for(int i = 0; i < l; i++)
            v_ones[i] = ones(i);

        mask = l - 1;
    };

    int _ones(int a) const
    {
        int count = 0;

        while(a)
        {
            count += v_ones[a & mask];
            a >>= k;
        }

        return count;
    };
    
    bool operator()(int a, int b) const
    {
        int ones_a = _ones(a);
        int ones_b = _ones(b);

        return ones_a < ones_b || (ones_a == ones_b && a < b);
    };
};


// Función principal para resolver el problema. Puede instanciarse con
// cualquiera de las relaciones de orden implementadas anteriormente.
// El algoritmo de ordenamiento implementado es Mergesort.
template<class Relation>
vector<int> msort(
    const vector<int> &v,
    const Relation &less_than,
    ssize_t i = 0,
    ssize_t j = -1)
{
    if(j == -1)
        j = v.size();

    if(i == j)
        return {};

    if(i == j-1)
        return {v[i]};

    ssize_t mid = i + (j-i)/2, i0 = 0, j0 = 0;
    vector<int> v1 = msort(v, less_than, i, mid);
    vector<int> v2 = msort(v, less_than, mid, j);
    vector<int> res;
 
    while(i0 < v1.size() && j0 < v2.size())
    {
        if(less_than(v1[i0], v2[j0]))
        {
            res.push_back(v1[i0]);
            i0++;
        }
        else
        {
            res.push_back(v2[j0]);
            j0++;
        }
    }

    for(; i0 < v1.size(); i0++)
        res.push_back(v1[i0]);


    for(; j0 < v2.size(); j0++)
        res.push_back(v2[j0]);

    return res;
}

void sort_array(std::vector<int> &A)
{
    A = msort(A, Relation2(14));
}
