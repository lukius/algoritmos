#include "palindrome.h"

// Para este problema exploramos dos variantes, detalladas a continuación.
// Si bien ambas tienen una complejidad temporal asintótica cuadrática en el
// tamaño de la lista, logramos establecer una comparación de eficiencia en
// función de la cantidad de movimientos de punteros de cada una.

// Primera variante:
//  * Para cada nodo j en la primera mitad de la lista, iterarar hacia su
//    pareja i y testear la igualdad entre sus datos.
//  * El nodo i buscado es tal que su siguiente corresponde al último nodo
//    visitado en la iteración anterior.
//  * El ciclo corta cuando, o bien j coincide con el último nodo visitado (que
//    se corresponde con una cantidad par de elementos en la lista), o bien
//    su siguiente coincide con dicho nodo (cuando la cantidad de elementos es
//    impar).
// Si notamos P_1(n) a la cantidad de movimientos de punteros que realiza este
// algoritmo, y asumiendo que n es impar, se observa que
//    P_1(n) = 𝚺 1+(n-1-2j), para j entre 0 y (n-3)/2
//           = n²/4 + n/2 - 3/4
bool is_palindrome_1(const list &l)
{
	for(
		const list *lj = &l, *last = nullptr, *li = lj;
		lj != last && lj->next != last;
		lj = lj->next, last = li, li = lj)
	{
		for(; li->next != last; li = li->next);
		if(li->data != lj->data)
			return false;
	}

	return true;
}

// Segunda variante:
//  * Computar la longitud n de la lista y ubicar el nodo emplazado en la
//    mitad.
//  * Para cada nodo j que le sigue (es decir, en la segunda mitad de la
//    lista), localizar su pareja i arrancando desde el comienzo y comprobar si
//    sus datos son iguales.
// La cantidad P_2(n) de movimientos de punteros de este algoritmo viene dada
// por
//    P_2(n) = n + (n-1)/2 + 𝚺  1+(n-1-j), para j entre (n+1)/2 y n-1
//           = n²/8 + 3n/2 + 3/8
// cuando n es impar.
// De esta manera, se tiene que P_2(n) < P_1(n) siempre que n ≥ 11.
bool is_palindrome_2(const list &l)
{
	int n = list_size(l), j = (n+1)/2;

	for(
		const list *lj = list_node(l, j), *li;
		lj != nullptr;
		lj = lj->next, ++j)
	{
		li = list_node(l, n-j-1);
		if(li->data != lj->data)
			return false;
	}

	return true;
}

// Funciones auxiliares utilizadas por is_palindrome_2.

int list_size(const list &l)
{
	int n = 0;
	for(
		const list *iter = &l;
		iter != nullptr;
		iter = iter->next, ++n);
	return n;
}

const list *list_node(const list &l, int i)
{
	const list *iter = &l;
	for(; i != 0 && iter != nullptr; --i)
		iter = iter->next;
	return iter;
}


bool is_palindrome(const list &l)
{
	return is_palindrome_2(l);
}


