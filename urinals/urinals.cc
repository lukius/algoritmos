#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Recordatorio del problema:
// Dado un arreglo M[1..n] de ceros y unos, formular un algoritmo que use la
// técnica de dividir y conquistar para encontrar la posición de algún cero
// que esté lo más alejado posible de un 1.
// 
// La solución que exploramos en este documento surge de descomponer M en tres
// partes, como muestra el siguiente diagrama:
// M = 0* | C | 0*
// en donde 0* representa una tira consecutiva de ceros (que puede ser nula) y
// C representa un arreglo arbitrario de ceros y unos.
// De esta forma, el objetivo será generalizar el valor de retorno del
// algoritmo de forma tal de computar los pares de valores (ik, dk) tales que
// ik indica la posición inicial de la máxima tira consecutiva de ceros de la
// porción k de M y dk representa su longitud, k = 1,2,3. Así, por ejemplo,
// (i2, d2) nos permite conocer la longitud máxima de una tira consecutiva de
// ceros en C e i2 la posición donde ésta comienza.

#define INF -1
#define SHOW_VALUE(n) ((n) == INF ? "∞" : to_string(n))

// Declaración de las funciones auxiliares para resolver el caso base y el caso
// general por separado.
ssize_t solve_base_case(
    const vector<int>&,
    ssize_t,
    vector<int>*,
    vector<ssize_t>*);

void solve_recursive_case(
    const vector<int>&,
    ssize_t, ssize_t,
    vector<int>*,
    vector<ssize_t>*);


// Función que implementa el esquema general de la solución. Observar que la
// complejidad temporal viene caracterizada por la recurrencia
// T(n) = 2T(n/2) + O(1)
// que, como ya sabemos, resuelve a O(n). De esta forma, obtenemos un algoritmo
// eficiente en tiempo (en cuanto a la comparación con la solución trivial
// iterativa) pero de complejidad espacial logarítmica. Desde ya, la solución
// iterativa es más conveniente no sólo por este hecho sino además por su
// simplicidad.
ssize_t choose_best_urinal(
    const vector<int> &M,
    ssize_t i, ssize_t j,
    vector<int> *_dist,
    vector<ssize_t> *_pos)
{
    if(j == -1)
        j = M.size();

    if(j - i == 1)
        return solve_base_case(M, i, _dist, _pos);

    vector<int> dist(3);
    vector<ssize_t> pos(3);

    solve_recursive_case(M, i, j, &dist, &pos);

    if(_dist != nullptr)
    {
        *_pos  = pos;
        *_dist = dist;
    }

    // * Si M está completamente lleno de ceros, basta tomar la primera
    //   posición.
    if(dist[0] == INF)
        return i;

    // * En otro caso, tenemos que contemplar cuál de las tres porciones de
    //   ceros es la máxima: la porción inicial, la mitad de la máxima porción
    //   central (puesto que en realidad buscamos el 0 más alejado de algún 1),
    //   o la porción final.
    ssize_t m = max({
                    dist[1] > 1 ? dist[1]/2 : dist[1],
                    dist[0],
                    dist[2]});

    // * Si el máximo es 0, M no tiene ningún cero disponible. De esta forma,
    //   devolvemos ∞.
    if(m == 0)
        return INF;
    // * Cuando la porción inicial es la más larga, la posición que maximiza la
    //   distancia a un 1 es precisamente la primera.
    if(m == dist[0])
        return i;
    // * De forma análoga, si la última porción es la más larga, nos quedamos
    //   con la última posición de M.
    else if(m == dist[2])
        return j-1;
    // * Por último, si la porción central es la más larga, tomamos el cero que
    //   aparece a mitad de camino.
    else
        return dist[1] > 1 ? pos[1] + m : pos[1];
}

// Resolución del caso base, que ocurre cuando |M| = 1.
ssize_t solve_base_case(
    const vector<int> &M,
    ssize_t i,
    vector<int> *dist,
    vector<ssize_t> *pos)
{
    // * Si M[0] = 0, las tres distancias buscadas son ∞. Además, la posición
    //   i1 es 0 y tanto i2 como i3 son también ∞.
    if(M[i] == 0)
    {
        if(dist != nullptr)
        {
            *dist = {INF, INF, INF};
            *pos  = {i, INF, INF};
        }

        return i;
    }
    // * Si M[0] = 1, al no haber mingitorios disponibles, cualquiera de las 
    //   tres posiciones puede entenderse como ∞, mientras que las distancias
    //   son todas nulas.
    else if(M[i] == 1)
    {
        if(dist != nullptr)
        {
            *dist = {0, 0, 0};
            *pos  = {INF, INF, INF};
        }

        return INF;
    }
}

// Resolución del caso general, que ocurre cuando |M| > 1.
void solve_recursive_case(
    const vector<int> &M,
    ssize_t i, ssize_t j,
    vector<int> *dist,
    vector<ssize_t> *pos)
{
    // Siendo M = M[i..j-1], lo que hacemos es particionar a M en dos mitades
    // M_1[i..k-1] y M_2[k..j-1] (k = (i+j)/2) y resolver ambos subproblemas
    // recursivamente a través de choose_best_urinal.
    size_t k = i + (j-i)/2;
    int d1, d2, d3, m;
    ssize_t i1, i2, i3;
    vector<int> dist_1(3), dist_2(3);
    vector<ssize_t> pos_1(3), pos_2(3);

    choose_best_urinal(M, i, k, &dist_1, &pos_1);
    choose_best_urinal(M, k, j, &dist_2, &pos_2);

    // Al volver de las llamadas, tendremos disponibles los arreglos dist_i y
    // pos_i para cada M_i, indicando respectivamente las distancias máximas en
    // cada porción de M_i y las posiciones iniciales. Para computar (i1,d1),
    // (i2,d2) e (i3,d3) para el arreglo completo M, basta considerar los
    // siguientes casos:
    //  * dist_1[0] < ∞:
    //    * Esto indica que M_1 contiene al menos un 1, de manera que su
    //      porción inicial de ceros no es vacía. De esta forma, la porción
    //      inicial de ceros de M representada por (i1, d1) toma exactamente
    //      los valores (pos_1[0], dist_1[0]).
    if(dist_1[0] != INF)
    {
        i1 = pos_1[0];
        d1 = dist_1[0];

        //  * Para computar (i2, d2) hay que analizar si la porción inicial de
        //    ceros de M_2 es vacía. Si no lo es, es necesario considerar un
        //    candidato dado por la concatenación entre la última porción de
        //    ceros de M_1 y la primera de M_2. La longitud de este candidato
        //    la indicamos con m en el código. Observar que m = 0 si la porción
        //    inicial de ceros de M_2 es vacía.
        m = 0;
        if(dist_2[0] != INF)
            m = dist_1[2] + dist_2[0];

        //  * d2, entonces, viene dado por el máximo valor entre m y las
        //    porciones máximas de ceros en las partes centrales de M_1 y M_2,
        //    dist_1[1] y dist_2[1] respectivamente. El valor final de i2 se
        //    ajusta de manera acorde en función de cuál de las tres distancias
        // sea la máxima.
        d2 = max({m, dist_1[1], dist_2[1]});

        if(d2 == dist_1[1])
            i2 = pos_1[1];
        else if(d2 == dist_2[1])
            i2 = pos_2[1];
        else if(d2 == m)
            i2 = dist_1[2] == 0 ? k : pos_1[2];


        //  * Finalmente, resta calcular (i3, d3). De forma similar a lo
        //    discutido más arriba, debemos comprobar si la última porción de
        //    ceros de M_2 es vacía. En caso de no serlo, i3 y d3 vienen dados
        //    por los valores ya computados para M_2. En caso contrario,
        //    tenemos que considerar la porción de ceros final de M_1 y
        //    concatenarle M_2. Observar que |M_2| = j - k.
        if(dist_2[2] != INF)
        {
            i3 = pos_2[2];
            d3 = dist_2[2];
        }
        else
        {
            i3 = dist_1[2] == 0 ? k : pos_1[2];
            d3 = dist_1[2] + j - k;
        }
    }
    //  * dist_1[0] = ∞: 
    else
    {
        // * En este caso, M_1 está completamente lleno de ceros. Por ende,
        //   debemos analizar qué ocurre con M_2.
        // * Si M_2 tiene al menos un 1, las valores correspondientes a las
        //   porciones central y final de M, (i2,d2) e (i3,d3), los podemos
        //   definir directamente en función de los respectivos valores M_2.
        // * En cuanto a (i1, d1), se observa que i1 = i (i.e., la posición
        //   inicial de M_1) y d_1 viene dado por la suma de |M_1| = k - i y la
        //   distancia de la porción inicial de ceros de M_2, dist_2[0].
        if(dist_2[0] != INF)
        {
            i1 = i;
            d1 = k - i + dist_2[0];

            i2 = pos_2[1];
            d2 = dist_2[1];

            i3 = pos_2[2];
            d3 = dist_2[2];
        }
        // * Por último, si M_2 tampoco tiene ningún 1, podemos tomar i1 = i y
        //   el resto de los valores ∞.
        else
        {
            i1 = i;
            d1 = d2 = d3 = i2 = i3 = INF;
        }
    }

    *pos  = {i1, i2, i3};
    *dist = {d1, d2, d3};
}



void show_solution(const vector<int> &M, bool print_newline =true)
{
    vector<int> dist(3);
    vector<ssize_t> pos(3);
    ssize_t i = choose_best_urinal(M, 0, -1, &dist, &pos);

    if(print_newline)
        cout << endl;

    cout << "M =";
    for(ssize_t j = 0; j < (ssize_t)M.size(); ++j)
        if(j == i)
            cout << " [" << M[j] << "]";
        else
            cout << " " << M[j];

    cout << " (i = " << SHOW_VALUE(i) << ")" << endl;

    cout << "(i1, d1) = ("; 
    cout << SHOW_VALUE(pos[0]) << ", " << SHOW_VALUE(dist[0]) << ")" << endl;

    cout << "(i2, d2) = ("; 
    cout << SHOW_VALUE(pos[1]) << ", " << SHOW_VALUE(dist[1]) << ")" << endl;

    cout << "(i3, d3) = ("; 
    cout << SHOW_VALUE(pos[2]) << ", " << SHOW_VALUE(dist[2]) << ")" << endl;
}

int main()
{
    vector<int> M;

    show_solution({1,1,1,1,1,1,1,1,1}, false);
    show_solution({0,0,0,0});
    show_solution({1,1,1,0,1,1});
    show_solution({0,1,1,0,0,0,0,1,1,1,0,0,1,0});
    show_solution({0,0,0,1,1,0,0,1,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0});

    return 0;
}
