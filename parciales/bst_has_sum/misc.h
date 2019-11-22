#ifndef _MISC_H_
#define _MISC_H_

#include "bst.h"

template<class T>
const bst<T> *max_node(const bst<T>*);

template<class T>
const bst<T> *min_node(const bst<T>*);

template<class T>
const bst<T> *successor(const bst<T>*);

template<class T>
const bst<T> *predecessor(const bst<T>*);

#endif
