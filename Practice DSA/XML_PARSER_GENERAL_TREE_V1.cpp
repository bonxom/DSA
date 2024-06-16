#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;
// Định nghĩa cấu trúc để lưu trữ thuộc tính của thẻ
typedef struct Attribute {
    char* name;
    char* value;
    struct Attribute* next;
} Attribute;

// Định nghĩa cấu trúc nút cây tổng quát cho thẻ HTML
typedef struct TreeNode {
    char* tag_name;
    Attribute* attributes;
    char* text;
    struct TreeNode* first_child;
    struct TreeNode* next_sibling;
    struct TreeNode* parent;
} TreeNode;

// Hàm tạo một thuộc tính mới
Attribute* create_attribute(char* name, char* value) {
    Attribute* attr = (Attribute*)malloc(sizeof(Attribute));
    attr->name = strdup(name);
    attr->value = strdup(value);
    attr->next = NULL;
    return attr;
}

// Hàm tạo một nút cây mới
TreeNode* create_tree_node(char* tag_name, char* text, TreeNode* parent) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->tag_name = strdup(tag_name);
    node->attributes = NULL;
    node->text = text ? strdup(text) : NULL;
    node->first_child = NULL;
    node->next_sibling = NULL;
    node->parent = parent;
    return node;
}

// Hàm thêm một thuộc tính vào nút
void add_attribute(TreeNode* node, char* name, char* value) {
    Attribute* attr = create_attribute(name, value);
    attr->next = node->attributes;
    node->attributes = attr;
}

// Hàm thêm một nút con vào nút cha
void add_child(TreeNode* parent, TreeNode* child) {
    if (parent->first_child == NULL) {
        parent->first_child = child;
    }
    else {
        TreeNode* sibling = parent->first_child;
        while (sibling->next_sibling != NULL) {
            sibling = sibling->next_sibling;
        }
        sibling->next_sibling = child;
    }
}


// Hàm giải phóng bộ nhớ của cây
void free_tree(TreeNode* node) {
    if (node == NULL) return;
    free_tree(node->first_child);
    free_tree(node->next_sibling);
    free(node->tag_name);
    if (node->text) free(node->text);
    Attribute* attr = node->attributes;
    while (attr != NULL) {
        Attribute* next = attr->next;
        free(attr->name);
        free(attr->value);
        free(attr);
        attr = next;    
    }
    free(node);
}

// Hàm đọc đến ký tự delimiter và trả về chuỗi kết quả
char* read_until(const char** str, char delimiter) {
    int capacity = 10;
    char* buffer = (char*)malloc(capacity);
    int length = 0;
    char ch;
    while ((ch = **str) != '\0' && ch != delimiter) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            buffer = (char*)realloc(buffer, capacity);
        }
        buffer[length++] = ch;
        (*str)++;
    }
    if (ch == delimiter) {
        (*str)++;
    }
    buffer[length] = '\0';
    return buffer;
}

// Hàm xoá các ký tự xuống dòng và các ký tự cách trống đầu, cuối trong chuỗi
char *remove_newlines(char* str) {
    // CODE tiếp tại đây
    bool rem[10000];
    memset(rem, 0, sizeof rem);
    for (int i = 1; i < (int)strlen(str); i++) {
        if (str[i] == '\n') rem[i] = true;
        if ((str[i] == ' ' || str[i] == '\n' || str[i] == '\r') && (str[i - 1] == '\n' || str[i - 1] == ' ' || str[i - 1] == '>' || str[i - 1] == '\r')) rem[i] = true;
    }
    string res = "";
    for (int i = 0; i < (int)strlen(str); i++) {
        if (rem[i] == false && str[i] != '\n' && str[i] != '\r') res = res + str[i];
    }
    return strdup(res.data());
}
char *tmpStr;
// Hàm kiểm tra thẻ tự đóng
int is_self_closing_tag(const char* tag_name) {
    string tmp = "/";
    for (int i = 0; i < (int)strlen(tag_name); i++) 
        tmp = tmp + tag_name[i];
    char *close_tag = strdup(tmp.data());
    if (strstr(tmpStr, close_tag) != NULL) return false; 
    return true;

}

// Hàm in cây theo cấu trúc cây tổng quát
void print_tree(TreeNode* node, int depth) {
    if (node == NULL) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("<%s", node->tag_name);
    Attribute* attr = node->attributes;
    while (attr != NULL) {
        printf(" %s=\"%s\"", attr->name, attr->value);
        attr = attr->next;
    }
    printf(">");
    bool isContainText = false;
    if (node->text != NULL)
    {

        printf("%s", node->text);
        isContainText = true;
    }
    else
        printf("\n");
    
    print_tree(node->first_child, depth + 1);
        
    if (!is_self_closing_tag(node->tag_name)) {
        if(node -> first_child != NULL) for (int i = 0; i < depth; i++) printf("  ");
        printf("</%s>\n", node->tag_name);
    }
        

    print_tree(node->next_sibling, depth);
}


string getName(char *str) {
    string newStr = "";
    for (int i = 0; i < (int)strlen(str); i++) { 
        if (str[i] == '<' || str[i] == '/') continue;
        if (str[i] == ' ' || str[i] == '>') break;
        newStr = newStr + str[i];
    }
    return newStr;
}
bool isClosingTag(char *str) {
    return str[1] == '/';
}
//ham tra ve mot nut hoan chinh
TreeNode* getNode(char *str) {
    string newStr = "";
    char *text = NULL;
    for (int i = 0; i < (int)strlen(str); i++) {
        if (str[i] == '<') continue;
        if (str[i] == '>') {
            if (i + 1 < (int)strlen(str) && str[i + 1] != '<') {
                const char* textStart = strstr(str, ">") + 1;
                text = read_until(&textStart, '<');
            }
            break;
        }
        newStr = newStr + str[i];
    }// newStr = tagname nameAt="valueAt"
    for (int i = 0; i < (int)newStr.size(); i++) 
        if (newStr[i] == '"' || newStr[i] == '=') newStr[i] = ' '; //newStr = tagname nameAt  Valueat
    stringstream ss;
    ss << newStr; //ss = (tagname, nameAt, valueAt)

    string tmp;
    ss >> tmp; // tmp = tagname
    char *nameTag = strdup(tmp.data());        
    TreeNode *result = create_tree_node(nameTag, text, NULL);

    char *nameAt, *valueAt;
    bool isValue = false;
    while (ss >> tmp) {//loop1: tmp = nameAt, loop2: tmp = valueAt
        if (isValue == false) {//loop1
            isValue = true;
            nameAt = strdup(tmp.data());
        }
        else {//loop2
            isValue = false;
            valueAt = strdup(tmp.data());
            add_attribute(result, nameAt, valueAt);
        }
    }
 
    return result;

}
// Hàm phân tích thẻ HTML và tạo cây
TreeNode* parse_html(const char* str) {
    TreeNode* root = NULL; 
    // CODE tiếp tại đây
    char *ptr = strdup(str);
    ptr++;
    ptr = strstr(ptr, "<");

    TreeNode *st[100];
    root = getNode(ptr);
    ptr = strstr(ptr + 1, "<");
    st[1] = root;
    int counter = 1;
    while (ptr != NULL) {
        string nameTag = getName(ptr);
        if (nameTag == st[counter] -> tag_name) { //closing tag => back to parent
            counter--;
        }
        else {
            TreeNode* node = getNode(ptr);
            //cout << node -> tag_name << " " << node -> text << endl;
            add_child(st[counter], node);
            counter++;
            st[counter] = node;
        }
        ptr = strstr(ptr + 1, "<");
    } 

   // cout << root -> first_child -> next_sibling -> text << endl;
    return root;
}


// Hàm đọc toàn bộ đầu vào từ bàn phím cho đến ^
char* read_all_input() {
    size_t capacity = 1024;
    char* buffer = (char*)malloc(capacity);
    size_t length = 0;

    int ch;
    while ((ch = getchar()) != '^') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            buffer = (char*)realloc(buffer, capacity);
        }
        buffer[length++] = ch;
    }
    buffer[length] = '\0';
    tmpStr = strdup(buffer);
    buffer = remove_newlines(buffer);
    // printf("%s/n", buffer);
    return buffer;
}

int main() {
    char* html_content = read_all_input();
    TreeNode* root = parse_html(html_content);

    if (root) {
        print_tree(root, 0);
        free_tree(root);
    }
    else {
        printf("Failed to parse XML.\n");
    }

    return EXIT_SUCCESS;
}
