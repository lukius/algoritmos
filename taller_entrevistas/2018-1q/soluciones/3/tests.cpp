#include <cassert>
#include <unistd.h>
#include <vector>

#include "maxnum.h"

using namespace std;


void test_zero_digits()
{
    vector<int> A;
    vector<int> B;
    int N;

    N = max_number(A, B, 0);
    assert(N == 0);

    A = {9, 5, 4, 3};
    B = {2, 7};
    N = max_number(A, B, 0);
    assert(N == 0);
}

void test_one_digit()
{
    vector<int> A {3, 9};
    vector<int> B {7, 8};
    int N;

    N = max_number(A, B, 1);
    assert(N == 9);

    A = {1, 7, 4, 3};
    B = {0, 6, 5, 5, 4};
    N = max_number(A, B, 1);
    assert(N == 7);
}

void test_several_digits()
{
    vector<int> A {3, 9};
    vector<int> B {8, 9};
    int N;

    N = max_number(A, B, 3);
    assert(N == 989);

    A = {3, 4, 6, 5};
    B = {9, 1, 2, 5, 8, 3};
    N = max_number(A, B, 5);
    assert(N == 98653);
}


//
// Main.

int main()
{
    test_zero_digits();
    test_one_digit();
    test_several_digits();

    return 0;
}
