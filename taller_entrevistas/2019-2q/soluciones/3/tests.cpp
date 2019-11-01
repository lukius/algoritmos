#include <cassert>
#include <unistd.h>
#include <vector>

#include "zeros.h"

using namespace std;


void test_empty()
{
    vector<int> A;
    bool result;

    result = has_zero_sum_elems(A);

    assert(!result);
}

void test_negative()
{
    vector<int> A;
    bool result;

    A = {-1, -2, -3};
    result = has_zero_sum_elems(A);
    assert(!result);

    A = {1, 2, 3};
    result = has_zero_sum_elems(A);
    assert(!result);

    A = {0, 0, -1};
    result = has_zero_sum_elems(A);
    assert(!result);

    A = {1, -1, 2, -7, 3};
    result = has_zero_sum_elems(A);
    assert(!result);
}

void test_positive()
{
    vector<int> A;
    bool result;

    A = {1, 2, -3};
    result = has_zero_sum_elems(A);
    assert(result);

    A = {0, 1, -1};
    result = has_zero_sum_elems(A);
    assert(result);

    A = {0, 0, 0, 0};
    result = has_zero_sum_elems(A);
    assert(result);

    A = {8, 9, 4, -1, 5, -6, 5, 2, 7};
    result = has_zero_sum_elems(A);
    assert(result);
}


//
// Main.

int main()
{
    test_empty();
    test_negative();
    test_positive();

    return 0;
}
