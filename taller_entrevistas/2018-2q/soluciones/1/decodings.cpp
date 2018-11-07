#include "decodings.h"

#define I(s,i) (10*(s[i]-0x30) + (s[i+1]-0x30))


// Algoritmo final visto en clase: considerar la función C(i) que indica la
// cantidad de decodificaciones posibles hasta el i-ésimo caracter de la
// secuencia s = s_1 .. s_n. Entonces,
// C(0) = 1  (caso artificial para que cierre la definición recursiva)
// C(1) = 1 si s_1 != 0 y 0 en otro caso
// C(i)  = | C(i-1) + C(i-2)  si s_i != 0 y 10 <= I(s_{i-1} s_i) <= 26
//         | C(i-1)           si s_i != 0 y no vale la desigualdad
//         | C(i-2)           si s_i = 0 y I(s_{i-1} s_i) es 10 ó 20
//         | 0                en otro caso
// Recordar que I(a b) indica el número decimal formado por los dígitos a y b
// en ese orden (i.e., I(a b) = 10*a + b).
// Observamos que esto permite calcular incrementalmente las decodificaciones,
// empezando desde el principio de la secuencia y avanzando de a una posición
// por vez. Puesto que C(i) sólo necesita conocer C(i-1) y C(i-2), no hace
// falta mantener un arreglo con los resultados parciales de C (con dos
// variables que se vayan actualizando al final de cada iteración es
// suficiente). Tenemos entonces una complejidad temporal lineal, lo cual es
// eficiente para este problema, y una complejidad espacial constante.
int num_decodings(const std::string &s)
{
	int c0 = 1, c1 = s[0] == '0' ? 0 : 1;
	
	for(size_t i = 1; i < s.size(); i++)
	{
		int I = I(s,i-1);
		if(10 <= I && I <= 26)
		{
			std::swap(c0, c1);
			if(s[i] != '0')
				c1 += c0;
		}
		else if(s[i] != '0')
			c0 = c1;
		else
			return 0;
	}
	
	return c1;
}

// Variante adicional (discutida pero ignorada): mantener la estructura
// recursiva original pero agregar memorización para evitar repetir cuentas y
// por ende mejorar la complejidad temporal (recordar que era exponencial).
int num_decodings_2(
		const std::string &s,
		size_t i,
		std::vector<int> *cache)
{
	if(i == s.size())
		return 1;
	if(s[i] == '0')
		return 0;
	if(i == s.size()-1)
		return 1;
	
	bool delete_cache = false;
	int decodings;
	
	if(cache == nullptr)
	{
		cache = new std::vector<int>(s.size()+1, -1);
		delete_cache = true;
	}
	
	if(cache->at(i+1) == -1)
		cache->at(i+1) = num_decodings_2(s, i+1, cache);
	cache->at(i) = cache->at(i+1);
	
	if(I(s,i) <= 26)
	{
		if(cache->at(i+2) == -1)
			cache->at(i+2) = num_decodings_2(s, i+2, cache);
		cache->at(i) += cache->at(i+2);
	}
		
	decodings = cache->at(i);
	
	if(delete_cache)
		delete cache;
	
	return decodings;
}