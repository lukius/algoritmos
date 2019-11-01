#include <algorithm>
#include <unordered_map>
#include <vector>
#include "max_number_of_As.h"


// Primera estrategia: algoritmo basado en la definición recursiva del
// problema. Si notamos A(n) a la máxima cantidad de As que pueden ser
// generadas presionando exactamente n teclas, tenemos que
//  * A(n) = n si n ≤ 3
//  * A(n) = máx { 1+A(n-1), 2A(n-3), 3A(n-4),..., (n-2)*A(1) } si n > 3
// En esta última igualdad, el primer miembro del conjunto del lado derecho
// surge de finalizar las n teclas presionando una A, mientras que los
// restantes miembros corresponden a pegar el buffer sucesivas veces. Para esto
// es necesario seleccionar y copiar previamente, de modo que como mínimo 
// debemos consumir tres teclas.
// Una implementación directa de esta fórmula no tendría sentido práctico
// debido a la repetición sistemática de cómputos derivada del solapamiento de
// los distintos subproblemas. Por este motivo, la siguiente función utiliza la
// técnica de memorización para tabular los resultados intermedios. La
// complejidad temporal asintótica resultante es O(n²).
int max_number_of_As_1(int n, std::unordered_map<int,int> *cache =nullptr)
{
    bool delete_cache = false;
    int An;

    if(n <= 3)
        return n;

    if(!cache)
        cache = new std::unordered_map<int,int>,
        delete_cache = true;

    if(cache->find(n) != cache->end())
        An = cache->at(n);
    else
    {
        An = max_number_of_As_1(n-1,cache) + 1;

        for(int i = 3; i <= n-1; i++)
            An = std::max(An, max_number_of_As_1(n-i,cache)*(i-1));

        cache->insert({n,An});
    }

    if(delete_cache)
        delete cache;

    return An;
}

// Esta nueva variante sigue la misma idea del primer algoritmo, aunque
// evitando la definición recursiva explícita. Este enfoque iterativo invierte
// el sentido de cómputo, de manera que sólo calcula los valores de A(i) 
// necesarios hasta alcanzar a A(n). La complejidad temporal resultante sigue
// siendo cuadrática.
int max_number_of_As_2(int n)
{
    std::vector<int> A(n+1);

    for(int i = 1; i < 4; i++)
        A[i] = i;

    for(int i = 4; i <= n; i++)
    {
        A[i] = A[i-1] + 1;
        for(int j = 3; j <= i-1; j++)
            A[i] = std::max(A[i], A[i-j]*(j-1));
    }

    return A[n];
}

int max_number_of_As(int n)
{
    return max_number_of_As_2(n);
}
