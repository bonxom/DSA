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
    // TNode *tmp = root->leftChild;
    // tmp->key = 11;
    return root;
}

void preOder(TNode *root){//TreeTraversal
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

bool find(TNode *root, int key){
    if (root == NULL) return false;
    if (root->key == key) return true;
    if (key < root->key) return find(root->leftChild, key);
    if (key > root->key) return find(root->rightChild, key);
}

TNode *search(TNode *root, int key){
    if (root == NULL) return NULL;
    if (root->key == key) return root;
    if (key < root->key) return search(root->leftChild, key);
    if (key > root->key) return search(root->rightChild, key);   
}

TNode *father = NULL;
bool isLeftChild = true;

TNode *search2(TNode *root, int key){// đi kèm việc tìm bố
    if (root == NULL) return NULL;
    if (root->key == key) return root;
    if (key < root->key) {
        father = root;
        isLeftChild = true;
        return search2(root->leftChild, key);
    }
    if (key > root->key){
        father = root;
        isLeftChild = false;
        return search2(root->rightChild, key);   
    } 
}

bool isBST(TNode *root){
    if (root == NULL) return true;
    if (root->leftChild != NULL && root->key < root->leftChild->key) return false;
    else if (root->rightChild != NULL && root->key > root->rightChild->key) return true;
    return isBST(root->leftChild) && isBST(root->rightChild);
}

void deleteNode(TNode *&root, int key){
    TNode *tmp = search2(root, key);
    if (tmp == NULL){
        cout << "NOT EXIST" << endl; return;
    }
    if (tmp->leftChild == NULL && tmp->rightChild == NULL){
        if (isLeftChild) father->leftChild = NULL;
        else father->rightChild = NULL;
    }
    free(tmp);
}
int main(){
    TNode *root = NULL;
    root = initTree();
    preOder(root); cout << endl;
    inOder(root); cout << endl;
    if (find(root, 7)) cout << "FOUND!" << endl;
    else cout << "NOT FOUND!"<< endl;

    TNode *tmp = search(root, 10);
    if (tmp == NULL) cout << "NOT EXIST!" << endl;
    else{
        cout << "EXIST: " << tmp->key << endl;
    }
    if (isBST(root)) cout << "is BST" << endl;
    else cout << "not BST" << endl;

    deleteNode(root, 6);
    cout << "DELETE LEAVE 6: ";
    preOder(root); cout << endl;
}