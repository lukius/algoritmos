#include <cassert>
#include "find_swapped_keys.h"


#define KEYS_OK(a,b,c,d) ((a==c && b==d) || (a==d && b==c))


void test_basic_tree()
{
    int k1, k2;
    bst l(2), t(1,&l,nullptr);
    bst r(1), t1(2,nullptr,&r);

    find_swapped_keys(&t, k1, k2);

    assert(KEYS_OK(k1,k2,1,2));

    find_swapped_keys(&t1, k1, k2);

    assert(KEYS_OK(k1,k2,1,2));
}

void test_keys_in_left_subtree()
{
    int k1, k2;
    bst ll(3), lr(1), r(7), l(2,&ll,&lr), t(5, &l, &r);

    find_swapped_keys(&t, k1, k2);

    assert(KEYS_OK(k1,k2,1,3));
}

void test_keys_in_right_subtree()
{
    int k1, k2;
    bst rlll(6), rll(5,&rlll,nullptr), rl(7,&rll,nullptr), rr(9),
        r(8,&rl,&rr), t(4, nullptr, &r);

    find_swapped_keys(&t, k1, k2);

    assert(KEYS_OK(k1,k2,5,6));
}

void test_keys_in_both_subtrees()
{
    int k1, k2;
    bst lr(10), l(3,nullptr,&lr), rr(4), r(9,nullptr,&rr), t(7,&l,&r);

    find_swapped_keys(&t, k1, k2);

    assert(KEYS_OK(k1,k2,10,4));
}


int main()
{
    test_basic_tree();
    test_keys_in_left_subtree();
    test_keys_in_right_subtree();
    test_keys_in_both_subtrees();

    return 0;
}
