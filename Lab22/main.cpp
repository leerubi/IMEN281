//
//  main.cpp
//  lab22
//
//  Created by ruby on 2017. 12. 12..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

class BinarySearchTree
{
public:
    struct tNode
    {
        tNode* left;
        tNode* right;
        int key;
    };
    
    tNode* root;
    
    BinarySearchTree()
    {
        root = NULL;
    }
    
    bool isEmpty() const { return root == NULL; }
    void insert(int num);
    void inorder_print(tNode* node);
    int find_level(tNode* left, int num);
};

void BinarySearchTree::insert(int num)
{
    tNode* t = new tNode;
    tNode* parent;
    t->key = num;
    t->left = NULL;
    t->right = NULL;
    parent = NULL;
    
    if (isEmpty()) root = t;
    else
    {
        tNode* curr;
        curr = root;
        while (curr)
        {
            parent = curr;
            if (t->key > curr->key) curr = curr->right;
            else curr = curr->left;
        }
        
        if (t->key < parent->key)
            parent->left = t;
        else
            parent->right = t;
    }
}

void BinarySearchTree::inorder_print(tNode* node)
{
    if (node == NULL)
        return;
    
    /* first recur on left child */
    inorder_print(node->left);
    
    /* then print the data of node */
    cout << node->key << " ";
    
    /* now recur on right child */
    inorder_print(node->right);
}


int BinarySearchTree::find_level(tNode* root, int _key)
{
    if (root == NULL)
        return 0;
    
    if(root->key == _key)
        return 1;
    
    if (root->key < _key)
    {
        if (find_level(root->right, _key) != 0)
            return find_level(root->right, _key) + 1;
        else return 0;
    }
    
    if (find_level(root->left, _key) != 0)
        return find_level(root->left, _key) + 1;
    else return 0;
}

int main(int argc, const char * argv[]) {
    // argv[1] = input_search_tree.csv
    BinarySearchTree search_tree;
    int num;
    char menu;
    string line;
    ifstream in(argv[1]);
    if (!in.is_open())
    {
        cout << argv[1] << " 파일이 열리지 않습니다." << endl;
    }
    // read inputfile and make a tree
    while (!in.eof()){
        getline(in, line);
        if(line != "")
            search_tree.insert(stoi(line));
    }
    in.close();
    
    while (true)
    {
        cout << "Enter menu(s:sort, f:find, e:exit): ";
        cin >> menu;
        if (menu == 'e') break;
        if (menu != 's' && menu != 'f')
        {
            cout << "다시 입력하세요." << endl;
            continue;
        }
        if (menu == 's'){
            search_tree.inorder_print(search_tree.root);
            cout << endl;
            //Inorder로 print
        }
        else if (menu == 'f'){
            cout << "Enter your number: ";
            cin >> num;
                
            int level = search_tree.find_level(search_tree.root, num);
            if (level == 0)
                cout << "No node" << endl;
            else
                cout << level << endl;
        }
    }
    return 0;
}
                     
