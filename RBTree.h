//  Sam Kujovich
//  RBTree.h
//  
//
//  Created by samuel a kujovich on 3/4/14.

#include "RBNode.h"
class RBTree
{
public:
    //Default Constructor
    RBTree();
    //Start at the root node and traverse the tree using preorder
    void printTree();
    //place a new node in the binary search tree with data the parameter and color it red.
    void addNode(int);
    //returns the sibling node of the parameter If the sibling does not exist, then return null.
    RBNode<int>* getSibling(RBNode<int>*);
    //returns the aunt of the parameter. If the aunt node does not exist, return null.
    RBNode<int>* getAunt(RBNode<int>*);
    //returns the grandparent of the parameter.
    RBNode<int>* getGrandparent(RBNode<int>*);
    //rotates left
    void rotateLeft(RBNode<int>*);
    //Rotates Right
    void rotateRight(RBNode<int>*);
    //
    void fixTree(RBNode<int>* current);
    //Destructor
    ~RBTree();
private:
    void print_pre(RBNode<int>* cursor);
    void delete_help(RBNode<int>*);
    RBNode<int>* root;
};
void RBTree::addNode(int new_data)
{
    RBNode<int>* cursor = root;
    if (root==NULL)
    {
        root = new RBNode<int> (new_data);
        root->set_color(RBNode<int>:: BLACK);
        fixTree(root);
        return;
    }
    while (cursor != NULL)
    {
        if (new_data < cursor->data())
        {
            if (cursor->left() == NULL)
            {
                cursor->left() = new RBNode<int>(new_data);
                cursor->left()->set_color(RBNode<int>:: RED);
                cursor->left()->set_parent(cursor);
                fixTree(cursor->left());
                break;
            }
            cursor=cursor->left();
        }
        else
        {
            if (cursor->right() == NULL)
            {
                cursor->right() = new RBNode<int>(new_data);
                cursor->right()->set_color(RBNode<int>:: RED);
                cursor->right()->set_parent(cursor);
                fixTree(cursor->right());
                break;
            }
            cursor=cursor->right();
        }
    }

}
RBTree::RBTree()
{
    root = NULL;
    return;
}

RBNode<int>* RBTree::getSibling(RBNode<int>* cursor)
{
    if (cursor == NULL)
        return NULL;
    else if (cursor == cursor->parent()->left())
        return cursor->parent()->right();
    else
        return cursor->parent()->left();
}
RBNode<int>* RBTree::getGrandparent(RBNode<int>* cursor)
{
    if (cursor == NULL)
        return NULL;
    else if (cursor->parent() == NULL)
        return NULL;
    else
        return cursor->parent()->parent();
}
RBNode<int>* RBTree::getAunt(RBNode<int>* cursor)
{
    if (cursor == NULL || cursor->parent() == NULL)
        return NULL;
    else if (cursor->parent() == cursor->parent()->parent()->left())
        return cursor->parent()->parent()->right();
    else
        return cursor->parent()->parent()->left();

}
void RBTree::print_pre(RBNode<int>* cursor)
{
	if (cursor == NULL)
	{
		return;
	}
	else
	{
		cout << cursor->data() << " ";
		print_pre(cursor->left());
		print_pre(cursor->right());
	}
}
void RBTree::printTree()
{
    print_pre(root);
    return;
}
void RBTree::delete_help(RBNode<int>* cursor)
{
    if (cursor == NULL)
	{
		return;
    }
    else
    {
        delete_help(cursor->left());
        delete_help(cursor->right());
    }
    delete cursor;
}
RBTree::~RBTree()
{
    delete_help(root);
}
void RBTree:: rotateRight(RBNode<int>* x)
{
    RBNode<int>* y = x->left();
    
    x->set_left(y->right());
    if(y->right() != NULL)
    {
        y->right()->set_parent(x);
    }
    y->set_parent(x->parent());
    if(x->parent() == NULL)
        root = y;
    else if(x == x->parent()->right())
        x->parent()->right() = y;
    else
    {
        x->parent()->left() = y;
    }
    y->set_right(x);
    x->set_parent(y);
    
}
void RBTree:: rotateLeft(RBNode<int>* x)
{
    RBNode<int>* y = x->right();
    
    x->set_right(y->left());
    if(y->left() != NULL)
    {
        y->left()->set_parent(x);
    }
    y->set_parent(x->parent());
    
    if(x->parent() == NULL)
        root = y;
    
    else if(x == x->parent()->left())
        x->parent()->left() = y;
    
    else
        x->parent()->right() = y;
    y->set_left(x);
    
    x->set_parent(y);
}
void RBTree::fixTree(RBNode<int>* current)
{
    if (current == root)
    {
        current->set_color(RBNode<int>:: BLACK);
        return;
    }
    if (current->parent()->color() == RBNode<int>:: BLACK)
        return;
    if(current->parent()->color() == RBNode<int>:: RED && current->color() == RBNode<int>:: RED)
    {
        if (getAunt(current) == NULL || getAunt(current)->color() == RBNode<int> :: BLACK)
        {
            if(current->parent()->parent()->left() == current->parent() && current == current->parent()->right())
            {
                RBNode<int>* original_parent = current->parent();
                rotateLeft(current->parent());
                fixTree(original_parent);
            }
            else if (current->parent()->parent()->right() == current->parent() && current == current->parent()->left())
            {
                RBNode<int>* original_parent = current->parent();
                rotateRight(current->parent());
                fixTree(original_parent);
            }
            else if(current->parent()->parent()->left() == current->parent() && current == current->parent()->left())
            {
                current->parent()->set_color(RBNode<int> :: BLACK);
                current->parent()->parent()->set_color(RBNode<int> :: RED);
                rotateRight(current->parent()->parent());
                return;
            }
            else if(current->parent()->parent()->right() == current->parent() && current == current->parent()->right())
            {
                current->parent()->set_color(RBNode<int> :: BLACK);
                current->parent()->parent()->set_color(RBNode<int> :: RED);
                rotateLeft(current->parent()->parent());
                return;
            }
        }
       else if (getAunt(current)->color() == RBNode<int> :: RED)
       {
            current->parent()->set_color(RBNode<int> :: BLACK);
            getAunt(current)->set_color(RBNode<int> :: BLACK);
            getGrandparent(current)->set_color(RBNode<int> :: RED);
            fixTree(getGrandparent(current));
            return;
        }
    }
}
