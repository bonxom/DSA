#include <stdio.h>
#include <stdlib.h>

struct TNode{
    char data;
    struct TNode* firstChild, *nextSibling;
};

typedef struct TNode TNode;

TNode* makeNode(char label){
    TNode *newNode = (TNode*)malloc(sizeof(TNode));
    newNode->data = label;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

void makeChild(TNode* root, char label){ //tạo anh họ ở ngoài cùng cho root
    TNode *newNode = makeNode(label);
    TNode *current = root->firstChild;
    if (current == NULL){
        current = newNode;
        root->firstChild = current;
        return;
    }
    while (current->nextSibling != NULL){
        current = current->nextSibling;
    }

    current->nextSibling = newNode;
}

TNode* initTree(){
    TNode* root = makeNode('A'); /// gốc A, có 3 con B, C, D
    makeChild(root, 'B');
    makeChild(root, 'C');
    makeChild(root, 'D');
    /// B có 2 con E, F;
    TNode* rootB = root->firstChild;
    makeChild(rootB, 'E');
    makeChild(rootB, 'F');
    /// E có 1 con G;
    makeChild(rootB->firstChild, 'G');
    ///D có 2 con K, H
    makeChild(rootB->nextSibling->nextSibling, 'K');
    makeChild(rootB->nextSibling->nextSibling, 'H');
    return root;
}

void preOrder(TNode *root){
    //process
    if (root == NULL) return;
    printf("%c, ", root->data);
    TNode* current = root->firstChild;
    while (current != NULL){
        preOrder(current);
        current = current->nextSibling;
    }
}

void postOrder(TNode *root){
    if (root == NULL) return;
    TNode* current = root->firstChild;
    while (current != NULL){
        postOrder(current);
        current = current->nextSibling;
    }
    //process
    printf("%c, ", root->data);
}

TNode* find(TNode *root, char label){//preOrder
    if (root == NULL) return NULL;
    if (root->data == label) return root;
    TNode* current = root->firstChild;
    while (current != NULL){//duyệt các NODE anh em
        TNode *res = find(current, label);
        if (res != NULL) return res;
        current = current->nextSibling;
    }
    return NULL;
} 

int Height(TNode *root){
    if (root == NULL) return -1;
    if (root->firstChild == NULL) return 0;
    int max_h = 0, child_h;

    TNode* current = root->firstChild;
    while (current != NULL){
        child_h = Height(current);
        if (child_h > max_h) max_h = child_h;
        current = current->nextSibling;
    }

    return 1 + max_h;
}

int Depth(TNode *root, char label, int d){ //TÌm độ sâu của 1 nút trên cây
    if (root == NULL) return -1;
    if (root->data == label) return d;
    TNode *p = root->firstChild;
    while (p != NULL){
        if (p->data == label) return d + 1; // độ sâu là d + 1(tính root);
        int dv = Depth(p, label, d + 1); // đệ quy đến các nút con của p
        if (dv > 0) return dv;
        p = p->nextSibling;
    }
    return -1;
}

int CountNodes(TNode *root){
    int cnt = 0;
    if (root == NULL) return 0;
    TNode *current = root->firstChild;
    while(current != NULL){
        cnt += CountNodes(current);
        current = current->nextSibling;
    }
    return cnt + 1;
}

int CountLeaves(TNode *root){
    int cnt = 0;
    if (root == NULL) return 0;
    TNode *current = root->firstChild;
    if (current == NULL){
        printf("%c ", root->data);
        return 1;
    }
    while (current != NULL){
        cnt += CountLeaves(current);
        current = current->nextSibling;
    }
    return cnt;
}

TNode *Parent(TNode *root, char label){
    if (root == NULL) return NULL;
    TNode *current = root->firstChild;
    if (current->data == label) return root;
    while (current != NULL){
        TNode *res = Parent(current, label);
        if (res != NULL) return res;
        current = current->nextSibling;
    }
    return NULL;
}

int main(){
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    TNode* root =  initTree();
    preOrder(root);
    printf("\n");
    postOrder(root);

    TNode *pos = find(root, 'N');
    if (pos != NULL) printf ("\nFound %c ", pos->data); else printf ("\nNULL");

    printf("\nHeight: %d", Height(root));

    printf("\nDepth E: %d", Depth(root, 'E', 0));

    printf("\nNodes: %d\n", CountNodes(root));

    printf("\nLeaves: %d", CountLeaves(root));

    TNode *Parent_of_E = Parent(root, 'E');
    if (Parent_of_E != NULL) printf ("\nParent is %c ", Parent_of_E->data); else printf ("\nNULL");
}
