//
//  tester.cpp
//  BinaryTree
//
//  Created by Teofana Moisi on 06/06/2018.
//  Copyright © 2018 Teofana Moisi. All rights reserved.
//

#include "tester.hpp"
#include <assert.h>
using namespace std;
#include <iostream>

Tester::Tester()
{}

Tester::~Tester()
{}

void Tester::test_node()
{
    Node* node = new Node;
    int e = 10;
    node->setInfo(e);
    assert(node->getInfo() == e);
    Node* left = new Node;
    left->setInfo(4);
    
    Node* right = new Node;
    right->setInfo(7);
    
    node->setLeft(left);
    node->setRight(right);
    
    Node* node_left = node->getLeft();
    Node* node_right = node->getRight();
    
    assert(node_left->getInfo() == 4);
    assert(node_right->getInfo() == 7);
    
    cout << "Node test passed. \n";
    
}


void Tester::test_tree()
{
    int e  = 8;
    BinaryTree bt{};
    
    BinaryTree left{};
    left.initLeaf(10);
    
    BinaryTree right{};
    right.initLeaf(4);
    
    BinaryTree subRight{};
    subRight.initLeaf(7);
    
    right.insertRightSubtree(subRight);
    
    BinaryTree subLeft{};
    subLeft.initLeaf(9);
    
    right.insertLeftSubtree(subLeft);
    
    
    BinaryTree subRightL{};
    subRightL.initLeaf(11);
    
    left.insertRightSubtree(subRightL);
    
    BinaryTree subLeftL{};
    subLeftL.initLeaf(34);
    
    left.insertLeftSubtree(subLeftL);
    
    
    bt.initTree(left, e, right);
    
    bool var = bt.isEmpty();
    assert(var == false);
    
//    int node = bt.getRoot();
//    assert(node == 8);
//
//    BinaryTree left_sub = bt.getLeft();
//    int left_root = left_sub.getRoot();
//    assert(left_root== 10);
//
//    BinaryTree right_sub = bt.getRight();
//    int right_root = right_sub.getRoot();
//    assert(right_root== 4);
    
    
    queue<int> res = bt.levelorderIterative();
    int n = res.front();
    assert(n == 8);
    assert(res.size() == 7);
    
    stack<int> stk = bt.inorderIterative();
    int in = stk.top();
    assert(in == 7);
    assert(stk.size() == 7);
    
    stack<int> stk_pre = bt.preorderIterative();
    int pre = stk_pre.top();
    assert(pre == 7);
    assert(stk_pre.size() == 7);
    
    stack<int> stk_post = bt.postorderIterative();
    int post = stk_post.top();
    assert(post == 8);
    assert(stk_post.size() == 7);
    
    
    Iter* it = bt.iterator("inorder");
    assert(it->valid() == true);
    int info = it->getCurrent();
    assert(info == 34);
    while(it->valid())
        it->next();
    assert(it->valid() == false);
    
    
    Iter* pre_it = bt.iterator("preorder");
    assert(pre_it->valid() == true);
    int p = pre_it->getCurrent();
    assert(p == 8);
    while(pre_it->valid())
        pre_it->next();
    assert(pre_it->valid() == false);
    
    Iter* lvl = bt.iterator("levelorder");
    assert(lvl->valid() == true);
    int l = lvl->getCurrent();
    assert(l == 8);
    while(lvl->valid())
        lvl->next();
    assert(lvl->valid() == false);
    
    
    Iter* post_it = bt.iterator("postorder");
    assert(post_it->valid() == true);
    int nr = post_it->getCurrent();
    assert(nr == 34);
    while (post_it->valid())
    {
        post_it->next();
    }
    assert(post_it->valid() == false);
    
    
    cout << "Binary tree test passes. \n";
    
}

void Tester::run()
{
    this->test_node();
    this->test_tree();
}
