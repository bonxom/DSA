#include <iostream>
#include <string>
#include <cstdlib>
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

TNode *initTree(){ // Khởi tạo cây ban đầu
    TNode *root = NULL;
    insert(root, 5);
    insert(root, 8);
    insert(root, 2);
    insert(root, 6);
    insert(root, 20);
    insert(root, 23);
    insert(root, 1); insert(root, 3);
    insert(root, 22); insert(root, 7);
    insert(root, 15); insert(root, 18); insert(root, 17); insert(root, 19);
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

bool find(TNode *root, int key){///// trả về true false
    if (root == NULL) return false;
    if (root->key == key) return true;
    if (key < root->key) return find(root->leftChild, key);
    if (key > root->key) return find(root->rightChild, key);
    return false;
}

TNode *findNode(TNode *root, int key){ //// trả về Node nếu tìm được, ngược lại trả về NULL
    if (root == NULL) return NULL;
    if (root->key == key) return root;
    if (key < root->key) return findNode(root->leftChild, key);
    if (key > root->key) return findNode(root->rightChild, key);   
    return NULL;
}

bool isBST(TNode *root){
    if (root == NULL) return true;
    if (root->leftChild != NULL && root->key < root->leftChild->key) return false;
    else if (root->rightChild != NULL && root->key > root->rightChild->key) return true;
    return isBST(root->leftChild) && isBST(root->rightChild);
}

TNode *findParent(TNode *root, int key, bool &isLeftChild){/// trả về bố của node key
                //// và trả về con trái hay phải thông qua truyền tham chiếu isLeftChild;
    if (root == NULL) return NULL;
    if (root->leftChild != NULL){
        if (root->leftChild->key == key){
            isLeftChild = true;
            return root;
        }
        else{
            TNode *res = findParent(root->leftChild, key, isLeftChild);
            if (res != NULL) return res;
        }
    }
    if (root->rightChild != NULL){
        if (root->rightChild->key == key){
            isLeftChild = false;
            return root;
        }
        else{
            TNode *res = findParent(root->rightChild, key, isLeftChild);
            if (res != NULL) return res;
        }
    }
    return NULL;
}

TNode *findMostLeft(TNode *root){// Tìm node trái nhất, tức là tìm Node có key min ấy
    while (root->leftChild != NULL){
        root = root->leftChild;
    }
    return root;
}

void deleteNode(TNode *& root, int key){ // có 4 TH xoá
    TNode *position = findNode(root, key);
    if (position == NULL){
        cout << "Key Not Found!!! \n"; return;
    }

    bool isLeftChild = true;
    TNode *parent = findParent(root, key, isLeftChild);
    if (position->leftChild == NULL && position->rightChild == NULL){
        cout << "Delete Leave\n";
        if (isLeftChild) parent->leftChild = NULL;
        else parent->rightChild = NULL;
        free(position); return;
    }

    if (position->leftChild == NULL && position->rightChild != NULL){
        cout << "Delete Node has only rightChild\n";
        if (isLeftChild) parent->leftChild = position->rightChild;
        else parent->rightChild = position->rightChild;
        free(position); return;
    }

    if (position->leftChild != NULL && position->rightChild == NULL){
        cout << "Delete Node has only leftChild\n";
        if (isLeftChild) parent->leftChild = position->rightChild;
        else parent->rightChild = position->rightChild;
        free(position); return;
    }

    if (position->leftChild != NULL && position->rightChild != NULL){
        cout << "Delete Node has 2 Children\n";
        //Thay position->key bằng mostLeft->key in right branch
        TNode *mostLeft = findMostLeft(position->rightChild);
        position->key = mostLeft->key;
        //Đưa rightChild của mostLeft lên thay mostLeft;
        bool left = true;
        TNode *parentOfMostleft = findParent(position, mostLeft->key, left);
        parentOfMostleft->leftChild = mostLeft->rightChild;
        free(mostLeft);
    }
}

int main(){
    TNode *root = NULL;
    root = initTree();
    preOder(root); cout << endl;
    inOder(root); cout << endl;
    if (find(root, 7)) cout << "FOUND!" << endl;
    else cout << "NOT FOUND!"<< endl;

    TNode *tmp = findNode(root, 19);
    if (tmp == NULL) cout << "NOT EXIST!" << endl;
    else{
        cout << "EXIST: " << tmp->key << endl;
    }
    if (isBST(root)) cout << "is BST" << endl;
    else cout << "not BST" << endl;

    cout << endl;
    bool isLeftChild = true;
    TNode *parent = findParent(root, 17, isLeftChild);
    if (parent != NULL){
        cout << "parent of 17: " << parent->key << endl;
        if (isLeftChild) cout << "isLeftChild" << endl;
        else cout << "isRightChild" << endl;
    }
    else cout << "Parent Not Found!!!\n";

    cout << endl;
    TNode *maxLeft = findMostLeft(root);
    cout << "mostleft Node of tree: " << maxLeft->key << endl;
    
    cout << endl;
    deleteNode(root, 8);
    cout << "Delete 8: ";
    preOder(root); cout << endl;
}