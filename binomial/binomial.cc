#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned int uint;
typedef pair<uint,uint> pair_t;
typedef map<pair_t,uint> cache_t;
typedef pair<pair_t,uint> cache_pair_t;


// C(n,k): cómputo naive, por definición, del coeficente binomial (n, k).
uint C(uint n, uint k)
{
    if(k == 0 || n == k)
        return 1;

    return C(n-1, k-1) + C(n-1, k);
}


// C_dp(n,k): cómputo "top-down", vía programación dinámica, del coeficiente
// binomial (n, k).
uint C_dp(uint n, uint k)
{
    if(k == 0 || n == k)
        return 1;
    
    uint c;
    vector<uint> fila_anterior({1,1});

    for(uint i = 2; i <= n; ++i)
    {
        vector<uint> fila_actual(i+1);
        fila_actual[0] = fila_actual[i] = 1;

        for(uint j = 1; j <= i/2; ++j)
        {
            fila_actual[j] = fila_actual[i-j] 
                           = fila_anterior[j-1] + fila_anterior[j];
            if(i == n && (j == k || j == n-k))
            {
                c = fila_actual[j]; 
                break;
            }
        }

        fila_anterior = fila_actual;
    }

    return c;
}


// C_mem(n,k): cómputo del coeficiente binomial (n, k) usando la definición
// recursiva clásica más una optimización adicional para evitar repetir
// cuentas (memoization).
uint C_mem(uint n, uint k, cache_t *cache=NULL)
{
    bool borrar_cache = false;

    if(cache == NULL)
    {
        cache = new cache_t();
        borrar_cache = true;
    }

    uint c;
    auto cacheado = cache->find({n,k});

    if(k == 0 || n == k)
        c = 1;
    else if(cacheado != cache->end())
        c = cacheado->second;
    else
    {
        c = C_mem(n-1, k, cache) + C_mem(n-1, k-1, cache);
        cache->insert(cache_pair_t({n,k}, c));
    }

    if(borrar_cache)
        delete cache;
    
    return c;
}

int main(int argc, char **argv)
{
    uint n, k;

    n = 6;
    k = 4;

    cout << "C(" << n << "," << k << ")     = ";
    cout.flush();
    cout << C(n,k) << endl;

    cout << "C_mem(" << n << "," << k << ") = ";
    cout.flush();
    cout << C_mem(n,k) << endl;

    cout << "C_dp(" << n << "," << k << ")  = ";
    cout.flush();
    cout << C_dp(n,k) << endl;

    n = 32;
    k = 15;

    cout << "C(" << n << "," << k << ")     = ";
    cout.flush();   
    cout << C(n,k) << endl;

    cout << "C_mem(" << n << "," << k << ") = ";
    cout.flush();
    cout << C_mem(n,k) << endl;

    cout << "C_dp(" << n << "," << k << ")  = ";
    cout.flush();
    cout << C_dp(n,k) << endl;
}
