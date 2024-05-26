/*Minh họa chueyern biểu thức dạng trung tố sang dạng hâu tố
Toán tử và toán hạng chỉ gồm 1 ký tự*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;

 

//Hàm kiểm tra xem có phải là toán tử
// hàm trả về 1 nếu ký tự op đúng là toán tử và 0 nếu ngược lại
int isOperator(char op)
{
    if ((op == '+') || (op == '-') || 
           (op == '*' )|| (op == '%' )|| 
           (op == '/' )|| (op == '^' )){
               return 1;
           }    
    return 0;  
}

 

/* Ham tra ve do uu tien cua toan tử
 chỉ xét 1 số toán tử cơ bản như + - * / % và ^
*/
int priority(char op)
{
    if((op == '+') || (op == '-')) {
        return 4;
    }
    if((op == '*' )|| (op == '%' )||(op == '/' )) {
        return 5;
    }
    if(op == '^'){
        return 6;
    }
    
    return 0;
}

 

// hàm chuyển biểu thức dạng trung tố sang dạng hậu tố
void chuyenSangHauTo(string eq)
{
    char ch;
    string retVal = "";

    stack<char> myStack;
    for(int i=0;i<eq.size(); i++)
    {
        if((eq[i]!='(')&&(eq[i]!=')')){
            if(!isOperator(eq[i]))//toan hang
            {
                retVal += eq[i];
            }
            else //toan tu
            {
                if(myStack.empty() || myStack.top()=='(' || 
                     priority(eq[i])==6 ||priority(eq[i])>priority(myStack.top())) 
                     {
                         myStack.push(eq[i]);
                     }
                else 
                {
                    ch = myStack.top(); 
                    while(!myStack.empty() && priority(eq[i]) <= priority(ch)) {
                        retVal += ch;
                        myStack.pop();
                        if(!myStack.empty()) ch = myStack.top(); 
                    }
                    myStack.push(eq[i]);    
                }  
            }
        }           
        else //dau ( hoac )
        {
            if(eq[i]=='(') myStack.push(eq[i]);
            else 
            {    
                ch=myStack.top();
                myStack.pop();
                while(ch!='(')
                {
                    retVal +=ch;
                    ch=myStack.top();  
                    myStack.pop();        
                }
            }
        }                                                                 
    }
    
    while(!myStack.empty()) //lay not cac toan tu con lai
    {
         ch=myStack.top();  
         myStack.pop();  
         retVal+=ch;
    }
    
    // gán ký tự cuối xâu
    cout << eq << " sang Hauto: " << retVal << endl;
}
 

// test code
int main()
{
    string ep;
    getline(cin, ep);
    chuyenSangHauTo(ep);
    return 0;
}