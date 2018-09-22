//
//  main.cpp
//  lab20
//
//  Created by ruby on 2017. 12. 6..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
    binaryTreeNode()
    {
        leftChild = rightChild = NULL;
    }
    // other constructors come here
};

template <class T>
void preOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template <class T>
void levelOrder(binaryTreeNode<T> *t)
{// Level-order traversal of *t.
    queue<binaryTreeNode<T>*> q;
    while (t != NULL)
    {
        visit(t);  // visit t
        // put t's children on queue
        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);
        
        if (q.size() == 0) return;
        
        // get next node to visit
        t = q.front();
        q.pop();
    }
}
class Node {
public:
    string id;
    string name;
    string leftChild;
    string rightChild;
    Node(string _id, string _name) : id(_id), name(_name) {}
};

int main(int argc, const char * argv[]) {
    binaryTreeNode<Node> * root;
    
    //set binary tree by read file(argv[1])
    ifstream fin(argv[1]);
    if (!fin.is_open())
        throw -1;
    string dummy;
    getline(fin, dummy);
    string id, name, l, r;
    while (!fin.eof()) {
        getline(fin, id, ',');
        if (id == "\n")
            break;
        getline(fin, name, ',');
        getline(fin, l, ',');
        getline(fin, r, '\r');
        root->element = Node(id, name);
        root->element.leftChild = l;
        root->element.rightChild = r;
    }
    fin.close();
    
    if (stoi(argv[2]) == 1)
    {
        cout << "Preorder :" << endl;
        preOrder(root);
        cout << endl;
    }
    
    if (stoi(argv[2]) == 2)
    {
        cout << "Level-order :" << endl;
        levelOrder(root);
        cout << endl;
    }
    return 0;

}
