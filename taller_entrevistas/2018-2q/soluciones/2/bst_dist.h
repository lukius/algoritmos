#ifndef _BST_DIST_H_
#define _BST_DIST_H_

#include <cmath>
#include <vector>

#include "bst.h"


#define SET_MIN(d) {     \
	if(min_d != nullptr) \
		*min_d = d;      \
}

// Consideremos nuestro abb t con raíz r. Pueden darse tres situaciones:
//  1. r = n, en cuyo caso simplemente podemos retornar una secuencia con r.
//  2. r < n, en donde observamos lo siguiente: si notamos d = |r - n| > 0,
//     todo nodo x en el subárbol izquierdo de t es tal que |x - n| > d (esto
//     se desprende de la propiedad de abb de t).  Así, la mínima distancia
//     buscada es d o bien surge del subárbol derecho de t.
//  3. r > n, que es una situación simétrica a la anterior.
// Esta observación permite derivar una estrategia recursiva para resolver el
// problema, en donde generalizamos el valor de retorno del algoritmo de forma
// de computar no sólo la secuencia de nodos que nos piden sino también la
// distancia. Esto lo hacemos para poder distinguir cuándo la distancia
// mínima es d y cuándo es la que viene de la llamada recursiva. 
// La complejidad temporal es lineal en la altura del árbol. Como se trata de
// un abb arbitrario, la altura puede degenerar en lineal en la cantidad de 
// nodos, de manera que la complejidad resulta lineal en la cantidad de nodos
// (nota: en este cálculo ignoramos las copias sucesivas del valor de retorno
// en la implementación dada puesto que es posible evitarlas).
template<class T>
std::vector<T> minimum_distance(
		const bst<T> &t,
		const T &n,
		int *min_d =nullptr)
{
	std::vector<T> result;
	int d = std::abs(t.root - n);
	
	SET_MIN(d);
	result.push_back(t.root);
	
	if(
		IS_LEAF(t) ||
		t.root == n ||
		(t.root < n && t.right == nullptr) ||
		(t.root > n && t.left == nullptr))
		return result;
	
	std::vector<T> l;
	int d_rec;
	
	if(t.root < n)
		l = minimum_distance(*t.right, n, &d_rec);
	else
		l = minimum_distance(*t.left, n, &d_rec);

	if(d_rec < d)
	{
		SET_MIN(d_rec);
		return l;
	}
	
	if(d_rec > d)
		return result;
	
	if(d_rec == d)
	{
		l.push_back(t.root);
		return l;
	}
}

#endif