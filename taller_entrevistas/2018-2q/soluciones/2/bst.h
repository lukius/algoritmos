#ifndef _BST_H_
#define _BST_H_

#define IS_LEAF(t) (t.left == nullptr && t.right == nullptr)

template<class T>
struct bst
{
	bst *left, *right;
	T root;
	
	bst(T root) : root(root)
	{
		this->left = nullptr;
		this->right = nullptr;
	};
	
	bst(T root, bst &left, bst &right) :
		left(&left),
		right(&right),
		root(root)
	{
	};
	
	bst(T root, bst &t, bool is_left_subtree =true) :
		left(nullptr),
		right(nullptr),
		root(root)
	{
		if(is_left_subtree)
			this->left = &t;
		else
			this->right = &t;
	};
};

#endif
