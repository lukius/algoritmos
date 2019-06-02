#include "climbing_ways.h"

// Para el primer ítem comenzamos identificando la estructura recursiva del
// problema: si notamos E(n) a la cantidad total de formas de subir los n
// escalones, surge que
//    E(n) = E(n-1) + E(n-2)  si n > 1
// con E(0) = E(1) = 1.
// Si bien esto deriva en un algoritmo recursivo inmediato, el solapamiento
// constante de los subproblemas degenera completamente el tiempo de ejecución,
// haciendo que este algoritmo carezca de utilidad práctica. No obstante, de
// igual forma que en el cálculo de los coeficientes binomiales, una inversión
// el sentido del cómputo logra eliminar este problema. La siguiente es una
// implementación iterativa de esta estrategia de complejidad lineal en n:
size_t climbing_ways_1(int n)
{
	if(n < 0) return 0;
	if(n <= 1) return 1;

	size_t e1 = 1, e2 = 1, e;

	for(int i = 2; i <= n; i++)
	{
		e = e1 + e2;
		e1 = e2;
		e2 = e;
	}

	return e2;
}

// Tambien estudiamos una optimización adicional que consiste en expresar la
// recurrencia en notación matricial de la siguiente forma:
//
// E = | 1 1 | * | E(n-1) | = | E(n) = E(n-1) + E(n-2)  |
//     | 1 0 |   | E(n-2) |   |        E(n-1)           |
//
// De esto se desprende que
//
// E^(n-1) * | E(1) | = |  E(n)  |
//           | E(0) |   | E(n-1) |
// 
// Luego, el problema se reduce a computar la exponenciación, problema para el
// cual ya estudiamos soluciones eficientes. En particular, podemos resolverlo
// en tiempo logarítmico en n a través de la función pow, mostrada más abajo.
size_t climbing_ways_2(int n)
{
	if(n < 0) return 0;
	if(n <= 1) return 1;

	std::vector<size_t> E {1, 1, 1, 0}, En;
	En = pow(E, n-1);

	return En[0] + En[1];
}

// Exponenciación de matrices en tiempo logarítmico siguiendo el algoritmo de
// exponenciación entera esbozado en clase.
// De manera un poco más formal, este algoritmo puede utilizarse para computar
// la exponenciación en cualquier monoide (M, o). Es decir, dado m en M y n un
// natural, este algoritmo permite computar
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
std::vector<size_t> pow(const std::vector<size_t> &M, int n)
{
	std::vector<size_t> Mn  {1, 0, 0, 1};
	std::vector<size_t> Msq {M};

	while(n)
	{
		if(n & 1)
			mul(Mn, Msq);

		mul(Msq, Msq);

		n >>= 1;
	}

	return Mn;
}

void mul(std::vector<size_t> &M1, const std::vector<size_t> &M2)
{
	size_t a, b, c, d;

	a = M1[0] * M2[0] + M1[1] * M2[2];
	b = M1[0] * M2[1] + M1[1] * M2[3];
	c = M1[2] * M2[0] + M1[3] * M2[2];
	d = M1[2] * M2[1] + M1[3] * M2[3];

	M1 = {a, b, c, d};
}

size_t climbing_ways(int n)
{
	return climbing_ways_2(n);
}

// Para el segundo ítem, extendimos la recurrencia original de la siguiente
// forma:
//          | 0            si n < 0
//    E(n) =| 1            si n = 0
//          | 𝚺 E(n-e_i)    si n > 0, para i = 1,...,k
//
// Una forma de transformar esta definición en un algoritmo eficiente es a
// través de la técnica de memorización, introduciendo un registro de los
// valores ya computados para evitar la repetición de cuentas. La siguiente
// función implementa esta idea logrando una complejidad temporal asintótica
// lineal en n:
size_t generic_climbing_ways(
	int n,
	const std::vector<int> &S,
	std::unordered_map<int,size_t> *values)
{
	if(n < 0) return 0;
	if(n == 0) return 1;
	
	size_t c = 0;
	bool clear_cache = false;
	
	if(values == nullptr)
	{
		values = new std::unordered_map<int,size_t>;
		clear_cache = true;
	}
	
	auto it = values->find(n);
	if(it != values->end())
		c = it->second;
	else
	{
		for(auto e : S)
			c += generic_climbing_ways(n-e, S, values);
		(*values)[n] = c;
	}
	
	if(clear_cache)
		delete values;
	
	return c;
}