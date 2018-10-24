 //
//  BinaryTree.cpp
//  BinaryTree
//
//  Created by Teofana Moisi on 06/06/2018.
//  Copyright © 2018 Teofana Moisi. All rights reserved.
//

#include "BinaryTree.hpp"
#include <stack>
#include <iostream>
#include <queue>
using namespace std;


Node* Node::getLeft()
{
    return this->left;
    
}

Node* Node::getRight()
{
    return this->right;
    
}

int Node::getInfo()
{
    return this->info;
    
}

void Node::setInfo(int e)
{
    this->info = e;
    
}
void Node::setLeft(Node* left)
{
    this->left = left;
}
void Node::setRight(Node* right)
{
    this->right = right;
    
}

Node::Node() {}
Node::~Node() {}


BinaryTree::BinaryTree(Node* root)
{
    this->root = root;
}
 
BinaryTree::~BinaryTree()
{
    this->destroy();
}

void BinaryTree::initLeaf(int e)
{
    Node* root = new Node;
    root->right = NULL;
    root->left = NULL;
    root->info = e;
    
    this->root = root;
    
}

//Node* BinaryTree::getRoot()
//{
//    return this->root->info;
//}

int BinaryTree::getRoot()
{
    return this->root->info;
}


void BinaryTree::initTree(BinaryTree& left, int e, BinaryTree& right)
{
    Node* root = new Node;
    root->info = e;
    root->left = left.root;
    root->right = right.root;
    
    
    this->root = root;
    
}

void BinaryTree::insertLeftSubtree(BinaryTree& left)
{
    this->root->left = left.root;
}

void BinaryTree::insertRightSubtree(BinaryTree& right)
{
    this->root->right = right.root;
}

BinaryTree BinaryTree::getLeft()
{
    BinaryTree left{ this->root->left};
    return left;
}

BinaryTree BinaryTree::getRight()
{
    BinaryTree right{ this->root->right};
    return right;
}

bool BinaryTree::isEmpty()
{
    if (this->root == NULL)
        return true;
    return false;
}

void BinaryTree::recursiveDestructor(Node* node)
{
    if (node != NULL)
    {
        this->recursiveDestructor(node->left);
        node->left = NULL;
        this->recursiveDestructor(node->right);
        node->left = NULL;
        node = NULL;
        delete node;
    }
}

void BinaryTree::destroy()
{
    this->recursiveDestructor(this->root);
}

Inorder::Inorder(BinaryTree& btree): bt(btree)
{
    Node* node = new Node;
    
    node = btree.root;
    this->stk = *new stack< Node *>;
    while (node != NULL)
    {
        this->stk.push(node);
        node = node->getLeft();
    }

    if (! stk.empty())
    {
        
        this->currentNode = this->stk.top();
        //stk.pop();
    }
    else
        this->currentNode = NULL;
}



int Inorder::getCurrent()
{
    return this->currentNode->getInfo();
}

bool Inorder::valid()
{
    if (this->currentNode == NULL)
        return false;
    return true;
}

void Inorder::next()
{
    Node* node = new Node;
    node = this->stk.top();
    stk.pop();
    if (node->getRight() != NULL)
    {
        node = node->getRight();
        while (node != NULL)
        {
            this->stk.push(node);
            node = node->getLeft();
            
        }
    }

    if (! this->stk.empty())
    {
        this->currentNode = this->stk.top();
        //stk.pop();
    }
    else
        this->currentNode = NULL;

}


Iter* BinaryTree::iterator(std::string traversal)
{
    if (traversal == "inorder")
    {
        Iter* it = new Inorder(*this);
        return it;
    }
    else if (traversal == "preorder")
    {
        Iter* it = new Preorder(*this);
        return it;
    }
    else if (traversal == "postorder")
    {
        Iter* it = new Postorder(*this);
        return it;
    }
    else
    {
        Iter* it = new Levelorder(*this);
        return it;
    }
    return NULL;
}

std::stack<int> BinaryTree::preorderIterative()
{
    stack<Node*> stk;
    stack<int> aux;
    Node* current = new Node;
    current = this->root;
    if (current != NULL)
        stk.push(current);
    
    while (!stk.empty())
    {
        current = stk.top();
        stk.pop();
        aux.push(current->getInfo());
        
        if (current->getRight() != NULL)
            stk.push(current->getRight());
        
        if (current->getLeft() != NULL)
            stk.push(current->getLeft());
    }
    return aux;
}

std::stack<int> BinaryTree::inorderIterative()
{
    stack<Node*> stk;
    stack<int> aux;
    Node* current = new Node;
    current = this->root;
    while (current != NULL)
    {
        stk.push(current);
        current = current->left;
    }

    while (! stk.empty())
    {
        //cout << current->info;
        current = stk.top();
        stk.pop();
        aux.push(current->getInfo());
        //cout << current->info << " " ;
        current = current->right;

        while (current != NULL)
        {
            stk.push(current);
            current = current->left;
        }
    }
    return aux;
}
std::stack<int> BinaryTree::postorderIterative()
{
    stack<Node*> stk;
    stack<int> aux;
    Node* node = new Node;
    node = this->root;
    
    while (node != NULL)
    {
        if (node->getRight() != NULL)
            stk.push(node->getRight());
        stk.push(node);
        node = node->getLeft();
    }
    
    while (!stk.empty())
    {
        node = stk.top();
        stk.pop();
        if ((node->getRight() != NULL) && (!stk.empty()) && (node->getRight() == stk.top()))
        {
            stk.pop();
            stk.push(node);
            node = node->getRight();
        }
        else
        {
            aux.push(node->getInfo());
            //cout << node->getInfo() << " ";
            node = NULL;
        }
        
        while (node != NULL)
        {
            if (node->getRight() != NULL)
                stk.push(node->getRight());
            stk.push(node);
            node = node->getLeft();
        }
        
    }
    return aux;
}

queue<int> BinaryTree::levelorderIterative()
{
    queue<Node*> q;
    queue<int> aux;
    
    q.push(this->root);
    
    while ( ! q.empty() )
    {
        Node* node = q.front();
        aux.push(node->getInfo());
        
        if ( node->getLeft() != NULL )
            q.push(node->getLeft());
        
        if ( node->getRight() != NULL )
            q.push(node->getRight());
        
        q.pop();
    }
    return aux;
}


Preorder::Preorder(BinaryTree& btree): bt(btree)
{
    Node* node = new Node;
    node = btree.root;
    this->stk = *new stack< Node *>;
    this->stk.push(node);
    this->next();
}

int Preorder::getCurrent()
{
    return this->currentNode->getInfo();
}

bool Preorder::valid()
{
    if (this->currentNode == NULL)
        return false;
    return true;
}

void Preorder::next()
{
    
    if (this->stk.empty())
    {
        this->currentNode = NULL;
        return;
    }
    Node* node = this->stk.top();
    stk.pop();
    this->currentNode = node;
    
    if (node->getRight() != NULL)
    {
        this->stk.push(node->getRight());
        
    }
    if (node->getLeft() != NULL)
    {
        this->stk.push(node->getLeft());
        
    }

}

Postorder::Postorder(BinaryTree& btree): bt(btree)
{
    
    Node* node = new Node;
    node = btree.root;
    while (node != NULL)
    {
        if (node->getRight() != NULL)
            this->stk.push(node->getRight());
        this->stk.push(node);
        node = node->getLeft();
    }
    if (!this->stk.empty())
    {
        this->currentNode = this->stk.top();
        this->stk.pop();
    }
    else
        this->currentNode = NULL;
}

int Postorder::getCurrent()
{
    return this->currentNode->getInfo();
}

bool Postorder::valid()
{
    if (this->currentNode == NULL)
        return false;
    return true;
}

void Postorder::next()
{
//
    if (this->stk.empty())
    {
        this->currentNode = NULL;
        return;
    }
    Node* node = new Node;
    node = this->stk.top();
    stk.pop();
    if ((node->getRight() != NULL) && (!this->stk.empty()) && (node->getRight() == this->stk.top()))
    {
        this->stk.pop();
        this->stk.push(node);
        node = node->getRight();
    }
    else
    {
        this->stk.push(node);
        node = NULL;
    }
    while (node != NULL)
    {
        if (node->getRight() != NULL)
            stk.push(node->getRight());
        stk.push(node);
        node = node->getLeft();
    }
    if (!this->stk.empty() && node == NULL)
    {
        this->currentNode = this->stk.top();
        this->stk.pop();
    }
    else
        this->currentNode = NULL;
    
    
}


Levelorder::Levelorder(BinaryTree& btree): bt(btree)
{
    Node* node = new Node;
    node = btree.root;
    this->q = *new queue<Node *>;
    q.push(node);
    this->next();
}


int Levelorder::getCurrent()
{
    return this->currentNode->getInfo();
}

bool Levelorder::valid()
{
    if (this->currentNode == NULL)
        return false;
    return true;
}

void Levelorder::next()
{
    if (q.empty())
    {
        this->currentNode = NULL;
        return;
    }
    Node* node = q.front();
    
    this->currentNode = node;
    
    if ( node->getRight() != NULL )
        q.push(node->getRight());
    
    if ( node->getLeft() != NULL )
        q.push(node->getLeft());
    
    q.pop();
}



