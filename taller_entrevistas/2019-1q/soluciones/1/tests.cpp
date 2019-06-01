#include <cassert>
#include "palindrome.h"


void test_singleton()
{
	list l(1);

	assert(is_palindrome(l));
}

void test_even_palindrome()
{
	list l4(1), l3(5, l4), l2(5, l3), l(1, l2);

	assert(is_palindrome(l));
}

void test_odd_palindrome()
{
	list l5(1), l4(5, l5), l3(7, l4), l2(5, l3), l(1, l2);

	assert(is_palindrome(l));
}

void test_non_palindrome()
{
	list l5(1), l4(5, l5), l3(7, l4), l2(5, l3), l(2, l2);

	assert(!is_palindrome(l));
}

int main()
{
	test_singleton();
	test_even_palindrome();
	test_odd_palindrome();
	test_non_palindrome();

	return 0;
}
