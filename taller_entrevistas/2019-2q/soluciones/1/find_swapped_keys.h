#ifndef _FIND_SWAPPED_KEYS_H_
#define _FIND_SWAPPED_KEYS_H_


struct bst
{
    bst(int root) : root(root), left(nullptr), right(nullptr) {}
    bst(int root, bst *left, bst *right) :
        root(root), left(left), right(right) {}
    
    int root;
    bst *left, *right;
};

void find_swapped_keys(bst*, int&, int&);

#endif
