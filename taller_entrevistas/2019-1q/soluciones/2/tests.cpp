#include <cassert>
#include "climbing_ways.h"


void test_climbing_ways()
{
	size_t c0 = climbing_ways(0);
	size_t c1 = climbing_ways(1);
	size_t c2 = climbing_ways(2);
	size_t c5 = climbing_ways(5);
	size_t c50 = climbing_ways(50);

	assert(c0 == 1);
	assert(c1 == 1);
	assert(c2 == 2);
	assert(c5 == 8);
	assert(c50 == 20365011074);
}

void test_generic_climbing_ways()
{
	size_t c0 = generic_climbing_ways(0, {1,2});
	size_t c1_1 = generic_climbing_ways(1, {1,5,7});
	size_t c1_2 = generic_climbing_ways(1, {2,5,7,9});
	size_t c5 = generic_climbing_ways(5, {1,3,5});
	size_t c50 = generic_climbing_ways(50, {1,3,5});

	assert(c0 == 1);
	assert(c1_1 == 1);
	assert(c1_2 == 0);
	assert(c5 == 5);
	assert(c50 == 3237119305);
}

int main()
{
	test_climbing_ways();
	test_generic_climbing_ways();

	return 0;
}
