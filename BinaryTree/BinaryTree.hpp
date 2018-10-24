//
//  BinaryTree.hpp
//  BinaryTree
//
//  Created by Teofana Moisi on 06/06/2018.
//  Copyright © 2018 Teofana Moisi. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp
#include <stack>
#include <string>
#include <stdio.h>
#include <queue>
class Iter;
class Inorder;
class Preorder;
class Postorder;
class Levelorder;

class Node
{
public:
    Node* getLeft();
    Node* getRight();
    int getInfo();
    
    void setInfo(int e);
    void setLeft(Node* left);
    void setRight(Node* right);
    Node();
    ~Node();
private:
    int info;
    Node* left;
    Node* right;
    
    friend class BinaryTree;
    friend class Inorder;
};





class BinaryTree
{
    
public:
    BinaryTree(Node* root = NULL);
    ~BinaryTree();
    void initLeaf(int e);
    void initTree(BinaryTree& left, int e, BinaryTree& right);
    //Node* getRoot();
    //int getRoot();
    void insertLeftSubtree(BinaryTree& left);
    void insertRightSubtree(BinaryTree& right);
    BinaryTree getLeft();
    BinaryTree getRight();
    bool isEmpty();
    Iter* iterator(std::string traversal);
    std::stack<int> inorderIterative();
    std::stack<int> postorderIterative();
    std::stack<int> preorderIterative();
    std::queue<int> levelorderIterative();

    
    
    
private:
    void destroy();
    void recursiveDestructor(Node* node);
    Node* root;
    int getRoot();

    
    
    friend class Iter;
    friend class Inorder;
    friend class Preorder;
    friend class Postorder;
    friend class Levelorder;
};

class Iter
{
public:
    virtual int getCurrent() = 0;
    virtual bool valid() = 0;
    virtual void next() = 0;
    virtual ~Iter() {}

private:
    BinaryTree bt;
    std::stack < Node * > stk;
    Node* currentNode;


};

class Inorder: public Iter
{

public:
    Inorder(BinaryTree& btree);
    int getCurrent() override;
    bool valid() override;
    void next() override;
    ~Inorder() {};

private:
    BinaryTree& bt;
    std::stack < Node * > stk;
    Node* currentNode;

    //friend class BinaryTree;
};

class Preorder: public Iter
{

public:
    Preorder(BinaryTree& btree);
    int getCurrent() override;
    bool valid() override;
    void next() override;

private:
    BinaryTree bt;
    std::stack < Node * > stk;
    Node* currentNode;

};

class Postorder: public Iter
{

public:
    Postorder(BinaryTree& btree);
    int getCurrent() override;
    bool valid() override;
    void next() override;

private:
    BinaryTree bt;
    std::stack < Node * > stk;
    Node* currentNode;

};

class Levelorder: public Iter
{

public:
    Levelorder(BinaryTree& btree);
    int getCurrent() override;
    bool valid() override;
    void next() override;

private:
    BinaryTree bt;
    std::stack < Node * > stk;
    std::queue < Node * > q;
    Node* currentNode;

};


#endif /* BinaryTree_hpp */
