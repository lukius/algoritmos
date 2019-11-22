#ifndef _BST_H_
#define _BST_H_

template<class T>
struct bst
{
    bst(T root) : root(root), left(nullptr), right(nullptr), up(nullptr) {}
    bst(T root, bst *left, bst *right, bst *up =nullptr) :
        root(root), left(left), right(right), up(up)
    {
        if(left)
            left->up = this;
        if(right)
            right->up = this;
    }
    
    T root;
    bst *left, *right, *up;
};

#endif
