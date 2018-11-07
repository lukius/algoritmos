#include <cassert>

#include "decodings.h"


void test_undecodable()
{
    int n1 = num_decodings("0");
    int n2 = num_decodings("01");
    int n3 = num_decodings("100");
    int n4 = num_decodings("1001");

    assert(n1 == 0);
    assert(n2 == 0);
    assert(n3 == 0);
    assert(n4 == 0);
}

void test_one_way()
{
    int n1 = num_decodings("1");
    int n2 = num_decodings("10");
    int n3 = num_decodings("2735");

    assert(n1 == 1);
    assert(n2 == 1);
    assert(n3 == 1);
}

void test_several_ways()
{
    int n1 = num_decodings("12");
    int n2 = num_decodings("226");
    int n3 = num_decodings("11111");

    assert(n1 == 2);
    assert(n2 == 3);
    assert(n3 == 8);
}


//
// Main.

int main()
{
    test_undecodable();
    test_one_way();
    test_several_ways();

    return 0;
}
