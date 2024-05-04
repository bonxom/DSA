#include <bits/stdc++.h>
using namespace std;

struct TNode{
    int key;
    TNode* leftChild;
    TNode* rightChild;
};

TNode *makeNode(int key){
    TNode *newNode = (TNode*)malloc(sizeof(TNode));
    newNode->key = key;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

void insert(TNode *&root, int key){
    if (root == NULL){
        root = makeNode(key); return;
    }
    if (key < root->key) insert(root->leftChild, key);
    else if (key > root->key) insert(root->rightChild, key);
    else{
        cout << "KEY EXISTED!!!\n"; return;
    }
}

TNode *initTree(){
    TNode *root = NULL;
    insert(root, 5);
    insert(root, 8);
    insert(root, 2);
    insert(root, 6);
    insert(root, 10);
    return root;
}

void preOder(TNode *root){
    if (root == NULL) return;
    cout << root->key << "  ";
    preOder(root->leftChild);
    preOder(root->rightChild);
}

void inOder(TNode *root){
    if (root == NULL) return;
    inOder(root->leftChild);
    cout << root->key << "  ";
    inOder(root->rightChild);
}

int main(){
    TNode *root = NULL;
    root = initTree();
    preOder(root); cout << endl;
    inOder(root);
}