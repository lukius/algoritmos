#include <cassert>
#include <cmath>
#include "closest_sum.h"


void test_one_pair()
{
	double d1 = closest_sum_to_target({1}, {4}, -2);
	double d2 = closest_sum_to_target({1}, {4}, 5);
	double d3 = closest_sum_to_target({1}, {4}, 15);

	assert(d1 == 7);
	assert(d2 == 0);
	assert(d3 == 10);
}

void test_misc()
{
	double d1 = closest_sum_to_target({2,3,-1,7}, {4,-2,1,-3}, 10);
	double d2 = closest_sum_to_target({2,3,-1,7}, {4,-2,1,-3}, 1);
	double d3 = closest_sum_to_target({2,3,-1,7}, {4,-2,1,-3}, 20);
	double d4 = closest_sum_to_target({2,3,-1,7}, {4,-2,1,-3}, -10);
	double d5 = closest_sum_to_target({2,3.5,-1,7}, {4,-2,1.5,-3}, 5.1);

	assert(d1 == 1);
	assert(d2 == 0);
	assert(d3 == 9);
	assert(d4 == 6);
	assert(std::abs(d5-0.1) < 1e-10);
}

int main()
{
	test_one_pair();
	test_misc();

	return 0;
}
