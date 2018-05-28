#include <cassert>
#include <vector>

#include "ones.h"

using namespace std;


void test_empty()
{
    vector<int> A;

    sort_array(A);

    assert(A.size() == 0);
}

void test_singleton()
{
    vector<int> A;
    
    A.push_back(5);
    sort_array(A);

    assert(A.size() == 1);
    assert(A[0] == 5);
}

void test_complex()
{
    vector<int> A;
    
    A.push_back(5);
    A.push_back(1);
    A.push_back(8);
    A.push_back(7);
    A.push_back(6);

    sort_array(A);

    assert(A.size() == 5);
    assert(A[0] == 1);
    assert(A[1] == 8);
    assert(A[2] == 5);
    assert(A[3] == 6);
    assert(A[4] == 7);
}


//
// Main.

int main()
{
    test_empty();
    test_singleton();
    test_complex();

    return 0;
}
