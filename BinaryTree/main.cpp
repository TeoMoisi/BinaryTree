//
//  main.cpp
//  BinaryTree
//
//  Created by Teofana Moisi on 05/06/2018.
//  Copyright © 2018 Teofana Moisi. All rights reserved.
//

#include <iostream>
#include "BinaryTree.hpp"
#include "tester.hpp"
using namespace std;


int search(int arr[], int strt, int end, int value)
{
    int i;
    for (i = strt; i <= end; i++)
    {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

BinaryTree* buildRecursive(int in[], int post[], int inStrt, int inEnd, int& pIndex)
{
    BinaryTree* tree = new BinaryTree;
    if (inStrt > inEnd)
        return tree;
    tree->initLeaf(post[pIndex]);
    //int node = tree->getRoot();
    int node = post[pIndex];
    pIndex--;

    if (inStrt == inEnd)
        return tree;

    int iIndex = search(in, inStrt, inEnd, node);

    BinaryTree* right = buildRecursive(in, post, iIndex+1, inEnd, pIndex);
    tree->insertRightSubtree(*right);

    BinaryTree* left = buildRecursive(in, post, inStrt, iIndex-1, pIndex);
    tree->insertLeftSubtree(*left);

    return tree;
}

BinaryTree* build(int in[], int post[], int n)
{
    int pIndex = n-1;
    return buildRecursive(in, post, 0, n - 1, pIndex);
}


void test_main()
{
    int arr[7] = {34, 10, 11, 8, 9, 4, 7};
    int res = search(arr, 0, 7, 11);
    assert(res == 2);
    
    int in[7] = {34, 10, 11, 8, 9, 4, 7};
    int post[7] = {34, 11, 10, 9, 7, 4, 8};
    int n = 7;
    
    BinaryTree* tree = build(in, post, n);
//    Node* node = tree->getRoot();
//    assert(node->getInfo() == 8);
    
    cout << "Test main passed.\n";
    
}


int main()
{
    
    Tester t;
    t.run();
    test_main();
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
    
    
    cout << "Inorder: ";
    stack<int> stk = bt.inorderIterative();
    stack<int> aux;
    while (!stk.empty())
    {
        int in = stk.top();
        stk.pop();
        aux.push(in);
    }
    while (!aux.empty())
    {
        int n = aux.top();
        aux.pop();
        cout << n << " ";
    }
    cout << "\n";
    cout << "Postorder: ";
    
    stack<int> stk_post = bt.postorderIterative();;
    stack<int> aux_post;
    while (!stk_post.empty())
    {
        int in = stk_post.top();
        stk_post.pop();
        aux_post.push(in);
    }
    while (!aux_post.empty())
    {
        int n = aux_post.top();
        aux_post.pop();
        cout << n << " ";
    }
    cout << "\n";
    
    cout << "Preorder: ";
    stack<int> stk_pre = bt.preorderIterative();;
    stack<int> aux_pre;
    while (!stk_pre.empty())
    {
        int in = stk_pre.top();
        stk_pre.pop();
        aux_pre.push(in);
    }
    while (!aux_pre.empty())
    {
        int n = aux_pre.top();
        aux_pre.pop();
        cout << n << " ";
    }
    cout << "\n";
    
    queue<int> q = bt.levelorderIterative();
    cout << "Levelorder: ";
    while (!q.empty())
    {
        int j = q.front();
        q.pop();
        cout << j << " ";
    }
    
    Iter* post_it = bt.iterator("levelorder");
    cout << "\nLevelorder_iter: ";
    while (post_it->valid())
    {
        int nr = post_it->getCurrent();
        cout << nr << " ";
        post_it->next();
    }
    

    
    cout << "\n";
    int n;
    cout << "Give the number of stations: \n";
    cin >> n;
    int* in = new int[n];
    cout << "Introduce the inorder traversal: ";
    for (int i = 0; i < n; i++)
    {
        cin >> in[i];
    }
    int* post = new int[n];
    cout << "Introduce the postorder traversal: ";
    for (int i = 0; i < n; i++)
    {
        cin >> post[i];
    }

    BinaryTree* tree = build(in, post, n);
    queue<int> lvl = tree->levelorderIterative();
    
    cout << "The level order of the stations is: ";
    while (!lvl.empty())
    {
        int j = lvl.front();
        lvl.pop();
        cout << j << " ";
    }
    cout << "\n";
    
    return 0;
}



