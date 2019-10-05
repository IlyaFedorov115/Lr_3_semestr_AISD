/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

int isDigit(char* str){
    if((str[0] == '-' || str[0] == '+' || isdigit(str[0])) && strlen(str)>1){
       for (int i = 1; i < strlen(str) ; i++){
            if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
    }
    else 
        return 0;
} 

int main()
{
    int a = 0;
    char buf[256];
    ifstream in("text", ios::in | ios::binary);
    while (in.getline(buf, 256, ' ')) {
     if (isDigit(buf))
        cout << "\nПоложит число" << atoi(buf);
     if (strlen(buf) == 1 && buf[0] == '+')
        cout << "\nСуммировать";
     if (strlen(buf) == 1 && buf[0] == '-')    
        cout << "\nРазность";
     if (!isDigit(buf) && strlen(buf) > 1)
        cout << "\nВведен некорректный символ: "<< buf[0];
    }
    return 0;
}










/******************************************************************************
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

int isDigit(char* str){
    if (((str[0] == '-' || str[0] == '+') && strlen(str)>1) || isdigit(str[0])){
   // if((str[0] == '-' || str[0] == '+' || isdigit(str[0])) && strlen(str)>1){
       for (int i = 1; i < strlen(str) ; i++){
            if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
    }
    else 
        return 0;
}

int main()
{
    int a = 0;
    char c;
    char buf[256];
    ifstream in("text", ios::in | ios::binary);
  //  while (cin.getline(buf, 256,' ') && cin.peek() != '\n') {
    // while (cin >> buf && cin.peek() != '\n') {
     do {
       cin >> buf;     
     if (isDigit(buf))
        cout << "\nПоложит число" << atoi(buf);
     if (strlen(buf) == 1 && buf[0] == '+')
        cout << "\nСуммировать";
     if (strlen(buf) == 1 && buf[0] == '-')    
        cout << "\nРазность";
     if (!isDigit(buf) && strlen(buf) > 1)
       cout << "\nERROR";
    }while(cin.peek() != '\n');
    cout << "STROKA:" << buf;
    return 0;
}
