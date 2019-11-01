#include <cassert>
#include "max_number_of_As.h"


void test_base_cases()
{
    assert(max_number_of_As(1) == 1);
    assert(max_number_of_As(2) == 2);
    assert(max_number_of_As(3) == 3);
}

void test_complex_cases()
{
    assert(max_number_of_As(7)  == 9);    
    assert(max_number_of_As(10) == 20);
    assert(max_number_of_As(15) == 81);
    assert(max_number_of_As(20) == 324);
}


int main()
{
    test_base_cases();
    test_complex_cases();

    return 0;
}
