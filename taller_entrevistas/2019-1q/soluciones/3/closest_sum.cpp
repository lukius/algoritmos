#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "closest_sum.h"

#define DIST(i,j) (std::abs((A1[i]+B1[j]) - k))

// La solución trivial de este problema involucra enumerar todos los posibles
// pares (i,j), 1 ≤ i,j ≤ n, y quedarse con la mínima distancia a k de entre
// todos ellos. Al haber Θ(n²) tales pares, la complejidad temporal asintótica
// resulta cuadrática. Esto nos motivó a continuar explorando soluciones más
// eficientes. En particular, observamos lo siguiente:
//  * Podemos ordenar ambos vectores puesto que no necesitamos preservar la
//    secuencialidad de sus elementos. Esto lo podemos hacer en tiempo
//    Θ(n log n).
//  * Si iteramos ambos arreglos arrancando desde los extremos opuestos, vemos
//    que, a medida que incrementamos los valores del extremo inferior, la
//    distancia a k irá decreciendo hasta eventualmente volver a crecer.
//  * Esto sugiere una estrategia de búsqueda que consiste en incrementar 
//    los valores del extremo inferior hasta identificar el mínimo local,
//    testear si dicho mínimo mejora el candidato visto hasta el momento, y
//    decrementar el valor del extremo superior para continuar el
//    procedimiento.
// Este algoritmo tiene un tiempo de ejecución Θ(n log n), de manera que mejora
// considerablemente la estrategia por fuerza bruta mencionada más arriba.
double closest_sum_to_target(
	const std::vector<double> &A,
	const std::vector<double> &B,
	double k)
{
	std::vector<double> A1(A);
	std::vector<double> B1(B);
	
	std::sort(A1.begin(), A1.end());
	std::sort(B1.begin(), B1.end());
	
	ssize_t n = A.size();
	double min_dist = DIST(0,n-1), d;
	
	for(
		ssize_t i = 0, j = n-1;
		i < n && j >= 0 && min_dist > 0;)
	{
		while(
			i < n &&
			(d=DIST(i,j)) > DIST(i+1,j))
			i++;
		
		min_dist = std::min(min_dist, d);
		
		j--;
	}
	
	return min_dist;
}