#ifndef _CLIMBING_WAYS_H_
#define _CLIMBING_WAYS_H_

#include <vector>
#include <unordered_map>
#include <cstdlib>

size_t climbing_ways(int n);
size_t generic_climbing_ways(
	int n,
	const std::vector<int> &S,
	std::unordered_map<int,size_t> * =nullptr);

std::vector<size_t> pow(const std::vector<size_t> &M, int n);
void mul(std::vector<size_t> &M1, const std::vector<size_t> &M2);

#endif