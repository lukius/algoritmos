#include <cassert>

#include "bst_dist.h"

void test_leaf()
{
	bst<int> t(5);

	std::vector<int> result = minimum_distance(t, 7);

	assert(result.size() == 1);
	assert(result[0] == 5);
}

void test_min_at_root()
{
	bst<int> right(10), left(5), t(8, left, right);

	std::vector<int> result = minimum_distance(t, 7);

	assert(result.size() == 1);
	assert(result[0] == 8);
}

void test_min_at_left()
{
	bst<int> right(10), left(5), t(8, left, right);

	std::vector<int> result = minimum_distance(t, 1);

	assert(result.size() == 1);
	assert(result[0] == 5);
}

void test_several_mins()
{
	bst<int> left(5);
	bst<int> rl(12), right(13, rl);
	bst<int> t(10, left, right);

	std::vector<int> result = minimum_distance(t, 11);

	assert(result.size() == 2);
	assert(result[0] == 12);
	assert(result[1] == 10);
}


//
// Main.

int main()
{
    test_leaf();
    test_min_at_root();
    test_min_at_left();
    test_several_mins();

    return 0;
}
