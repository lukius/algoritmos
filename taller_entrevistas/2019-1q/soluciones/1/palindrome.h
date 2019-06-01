#ifndef _PALINDROME_H_
#define _PALINDROME_H_

struct list
{
    list(int data) : data(data), next(nullptr) {}
    list(int data, list &next) : data(data), next(&next) {}
    
    int data;
    list *next;
};

bool is_palindrome(const list &l);
bool is_palindrome_1(const list &l);
bool is_palindrome_2(const list &l);


#endif
