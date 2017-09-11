#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> pow(const vector<int>&, int);


// Este documento contiene tres algoritmos para calcular los términos de
// recurrencias lineales homogéneas de segundo orden, tomando como ejemplo
// paradigmático la sucesión de Fibonacci.


// Primer acercamiento: utilizando la propia definición de la recurrencia, los
// términos de la sucesión se computan de forma recursiva. El solapamiento
// entre las distintas llamadas hace que se repitan cuentas, volviendo al
// algoritmo extremadamente ineficiente e inútil en la práctica.
int recu_1(
    int n, 
    const vector<int> &coefs,
    const vector<int> &ci)
{
    if(n < 2)
        return ci[n];

    return coefs[0] * recu_1(n-1, coefs, ci) +
           coefs[1] * recu_1(n-2, coefs, ci);
}


// Segundo algoritmo, por programación dinámica. De forma iterativa, esta
// estrategia arranca desde las condiciones iniciales y genera sucesivamente
// los términos intermedios de la sucesión hasta arribar al n-ésimo. Observar
// que ya no se repiten cuentas: cada término se visita una única vez. Por este
// motivo, su complejidad temporal es lineal en n, lo cual arroja una mejora
// exponencial respecto del algoritmo recursivo por definición.
int recu_2(
    int n, 
    const vector<int> &coefs,
    const vector<int> &ci)
{
    if(n < 2)
        return ci[n];

    int s_0 = ci[0], s_1 = ci[1], s_2;

    while(true)
    {
        n--;
        s_2 = coefs[0] * s_1 + coefs[1] * s_0; 

        if(n == 1)
            return s_2;

        swap(s_0, s_1);
        swap(s_1, s_2);
    }
}


// Tercera y última variante. Dada una recurrencia lineal homogénea de segundo
// orden S,
//
// S(n) = aS(n-1) + bS(n-2); S(0) = s_0, S(1) = s_1
//
// podemos expresarla en notación matricial de la siguiente forma:
//
//M = | a b | * | S(n-1) | = |  S(n)  |
//    | 1 0 |   | S(n-2) |   | S(n-1) |
//
// De esto se desprende que
//
// M^(n-1) * | s_1 | = |  S(n)  |
//           | s_0 |   | S(n-1) |
// 
// Luego, el problema se reduce a computar la exponenciación, problema para el
// cual ya estudiamos soluciones eficientes. En particular, podemos resolverlo
// en tiempo logarítmico en n (ver más abajo).
// 
// Observar que este enfoque puede generalizarse a recurrencias lineales de
// orden arbitrario, aunque la complejidad resultante depende del algoritmo
// que decida utilizarse para multiplicar dos matrices.
int recu_3(
    int n, 
    const vector<int> &coefs,
    const vector<int> &ci)
{
    if(n < 2)
        return ci[n];

    vector<int> M {coefs[0], coefs[1], 1, 0}, Mn;
    Mn = pow(M, n-1);

    return Mn[0] * ci[1] +
           Mn[1] * ci[0];
}


// Multiplicación trivial de matrices de 2x2.
void mul(
    vector<int> &M1,
    const vector<int> &M2)
{
    int a, b, c, d;

    a = M1[0] * M2[0] + M1[1] * M2[2];
    b = M1[0] * M2[1] + M1[1] * M2[3];
    c = M1[2] * M2[0] + M1[3] * M2[2];
    d = M1[2] * M2[1] + M1[3] * M2[3];

    M1 = {a, b, c, d};
}

// Exponenciación de matrices en tiempo logarítmico, a partir del algoritmo
// iterativo mencionado en clase. Observar que es esencialmente el mismo
// algoritmo con la obvia diferencia en cuanto a cómo resolver la
// multiplicación de los objetos involucrados.
// 
// (Opcional) De manera un poco más formal, este algoritmo puede utilizarse
// para computar la exponenciación en cualquier monoide (M, o). Es decir, dado
// m en M y n un natural, este algoritmo permite computar
//
// m^n = m o m ... o m (n veces)
//
// en tiempo O(f * log n), siendo O(f) el tiempo de computar la operación del
// monoide.
//
// En el caso de la exponenciación entera, el monoide en consideración es
// (N, *) con elemento neutro (o identidad) 1, mientras que en el caso de las
// matrices de 2x2 la operación es la multiplicación standard de matrices con
// la matriz identidad usual como elemento neutro.
vector<int> pow(
    const vector<int> &M,
    int n)
{
    vector<int> Mn  {1, 0, 0, 1};
    vector<int> Msq {M};

    while(n)
    {
        if(n & 1)
            mul(Mn, Msq);

        mul(Msq, Msq);

        n >>= 1;
    }

    return Mn;
}


void calcular(
    int n,
    const string &id,
    const vector<int> &coefs,
    const vector<int> &ci,
    bool  con_recu_1=true)
{
    if(con_recu_1)
    {
        cout << "(recu_1) " << id << "(" << n << ") = ";
        cout.flush();
        cout << recu_1(n, coefs, ci) << endl;
    }

    cout << "(recu_2) " << id << "(" << n << ") = ";
    cout.flush();
    cout << recu_2(n, coefs, ci) << endl;

    cout << "(recu_3) " << id << "(" << n << ") = ";
    cout.flush();
    cout << recu_3(n, coefs, ci) << endl << endl;
}


int main(int argc, char **argv)
{
    vector<int> coefs_fib {1 , 1};
    vector<int> ci_fib    {0, 1};

    calcular(10, "fib", coefs_fib, ci_fib);
    calcular(42, "fib", coefs_fib, ci_fib);

    cout << "R(n) = 2R(n-1) - 3R(n-2); R(0) = -2; R(1) = 6" << endl << endl;

    calcular(42,        "R", {2, -3}, {-2, 6});
    calcular(100000000, "R", {2, -3}, {-2, 6}, false);
}
