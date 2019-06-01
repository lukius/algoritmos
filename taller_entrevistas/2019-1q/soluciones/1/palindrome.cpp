#include "palindrome.h"

int list_size(const list &l)
{
	int n = 0;
	for(
		const list *iter = &l;
		iter != nullptr;
		iter = iter->next, ++n);
	return n;
}

const list *list_node(const list &l, int i)
{
	const list *iter = &l;
	for(; i != 0 && iter != nullptr; --i)
		iter = iter->next;
	return iter;
}

bool is_palindrome_1(const list &l)
{
	for(
		const list *lj = &l, *last = nullptr, *li = lj;
		lj != last && lj->next != last;
		lj = lj->next, last = li, li = lj)
	{
		for(; li->next != last; li = li->next);
		if(li->data != lj->data)
			return false;
	}

	return true;
}

bool is_palindrome_2(const list &l)
{
	int n = list_size(l), j = (n+1)/2;

	for(
		const list *lj = list_node(l, j), *li;
		lj != nullptr;
		lj = lj->next, ++j)
	{
		li = list_node(l, n-j-1);
		if(li->data != lj->data)
			return false;
	}

	return true;
}

bool is_palindrome(const list &l)
{
	return is_palindrome_2(l);
}


