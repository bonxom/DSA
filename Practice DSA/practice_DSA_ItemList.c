#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai báo cấu trúc dữ liệu cho sản phẩm
typedef struct Item {
    char ID[12];
    int quantity;
    char insertDate[21];
    double price;
    struct Item* next;
} Item;

// Hàm để thêm một sản phẩm vào giỏ hàng
void addItem(Item** head, char ID[], int quantity, char insertDate[], double price) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->ID, ID);
    newItem->quantity = quantity;
    strcpy(newItem->insertDate, insertDate);
    newItem->price = price;
    newItem->next = NULL;

    if (*head == NULL) {
        *head = newItem;
    }
    else {
        Item* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

// Hàm để đọc thông tin các sản phẩm input
void readItemList(Item** head) {
    char ID[12];
    int quantity;
    char insertDate[21];
    char nextLine[100];
    double price;
    int count = 0;
    while (1) {
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%s", ID);
        if (strlen(ID) == 0) continue;
        if (strcmp(ID, "-1") == 0) {
            break;
        }

        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%d", &quantity);

        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        strcpy(insertDate, nextLine);

        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%lf", &price);

        count++;
        addItem(head, ID, quantity, insertDate, price);
    }
    printf("Total: %d\n", count);
}
/////////////////////////////////////////////////////////////////////////////////
// PHẦN CODE LÀM CỦA SINH VIÊN
//////////////////////////////////////////////////
// Hàm tính tổng tiền sản phẩm trong giỏ hàng
double checkCartTotalPrice(Item* head) {
  // SINH VIÊN CODE TIẾP VÀO ĐÂY
      double price = 0;
    while (head != NULL){
        price += (head->price) * (head->quantity);
        head = head->next;
    }
    return price;
}
 
// Hàm để tìm kiếm sản phẩm theo mã ID
// Trả về NULL nếu không tìm thấy
// ngược lại trả về địa chỉ của phần tử chứa ID
Item* findanItemByID(Item* head, char ID[]) {
  // SINH VIÊN CODE TIẾP VÀO ĐÂY
    while (head != NULL){
        if (strcmp(head->ID, ID) == 0 && head->quantity > 0) return head;
        head = head->next;
    }
  return NULL; 
}
 
 
// Hàm giảm số lượng 1 mã sản phẩm
// Nếu số lượng sản phẩm trong giỏ hàng ít hơn hoặc bằng số lượng // cần giảm thì xóa sản phẩm đó khỏi giỏ hàng
// hàm trả về 1 nếu điều chỉnh thành công và 0 nếu không thành công // (ID không tìm thấy)
int reduceItemQuantityByID(Item** head, char ID[], int reduceQuantity) {
  // SINH VIÊN CODE TIẾP VÀO ĐÂY
  Item *tmp = findanItemByID(*head, ID);
  if (tmp != NULL){
    tmp->quantity = tmp->quantity - reduceQuantity;
    return 1;
  }
  return 0;
}
 

// Hàm để thêm một sản phẩm vào giỏ hàng, nếu đã có thì tăng số
// lượng lên, nếu chưa có thì thêm vào cuối danh sách
// các thông tin được truyền như tham số hàm, ý nghĩa các trường 
// giống như tên trường
void addNewItem(Item** head, char ID[], int quantity, char insertDate[],  double price) {
    Item *tmp = findanItemByID(*head, ID);
    if (tmp != NULL) (tmp->quantity) += quantity;
    else addItem(head, ID, quantity, insertDate, price);
}



///////////////////////////////////////////////////
// HẾT PHẦN LÀM CỦA SINH VIÊN
////////////////////////////////////////////////////////////////////////////////

void findItemsByID(Item* head)
{
    char ID[11], nextLine[100];;
    Item* anItem = NULL;
    while (1) {
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%s", ID);

        if (strcmp(ID, "-1") == 0) {
            break;
        }
        anItem = findanItemByID(head, ID);
        if (anItem == NULL) printf("Item NOT FOUND\n");
        else printf("Item's already added at %s\n", anItem->insertDate);
    }
}




void reduceItemQuantityByIDs(Item** head)
{
    char ID[12], nextLine[100];
    int reduceQuantity;
    while (1) {
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%s %d", ID, &reduceQuantity);
        if (strcmp(ID, "-1") == 0) {
            break;
        }
        if (reduceItemQuantityByID(head, ID, reduceQuantity))
            printf("DONE Remove\n");
        else
            printf("ID NOT FOUND\n");
    }
}



// Hàm để đọc thông tin các sản phẩm input
void addNewItems(Item** head) {
    char ID[12];
    int quantity;
    char insertDate[21];
    char nextLine[100];
    double price;
    while (1) {
        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%s", ID);
        if (strlen(ID) == 0) continue;
        if (strcmp(ID, "-1") == 0) {
            break;
        }

        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%d", &quantity);

        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        strcpy(insertDate, nextLine);

        fgets(nextLine, sizeof(nextLine), stdin);
        nextLine[strcspn(nextLine, "\r\n")] = 0;
        sscanf(nextLine, "%lf", &price);

        addNewItem(head, ID, quantity, insertDate, price);
    }
}
// Hàm để test các hàm đã định nghĩa ở trên

int main() {
    Item* cartList = NULL;
    char nextCommand[100];
    while (1)
    {
        fgets(nextCommand, sizeof(nextCommand), stdin);
        nextCommand[strcspn(nextCommand, "\r\n")] = 0;
        if (nextCommand[0] != '?') break;
        if (strcmp(&nextCommand[2], "readCart") == 0)
            readItemList(&cartList);
        else if (strcmp(&nextCommand[2], "findItemsByID") == 0)
            findItemsByID(cartList);
        else if (strcmp(&nextCommand[2], "reduceItemQuantityByIDs") == 0)
            reduceItemQuantityByIDs(&cartList);
        else if (strcmp(&nextCommand[2], "addNewItems") == 0)
            addNewItems(&cartList);
        else if (strcmp(&nextCommand[2], "checkCartTotalPrice") == 0)
            printf("Total price: %.2lf\n", checkCartTotalPrice(cartList));
    }

    return 0;
}
