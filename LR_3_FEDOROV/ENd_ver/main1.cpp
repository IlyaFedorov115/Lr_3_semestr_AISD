#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define SIZE 500
string file = "f";
string con = "c";
string stop = "n";
string again = "y";

int step = 1;



class stack{
  private:
    int array[SIZE];
    int topElem;
    int size;
  public:
    stack();
    bool isEmpty();
    int push(int a);
    void pop();
    int top();
    int pop2();
    bool isOne();
 
};

/*
stack::stack(int maxsize = SIZE){
    array = new int [maxsize];
    int size = maxsize;
    int topElem = -1;
} */

stack::stack(){
   // array = new int [SIZE];
     size = 0;
     topElem = -1;
}

/*
stack::stack(const stack &ob){
    int size = ob.size;
    int topElem = ob.topElem;
    array = new int [size];
    for (int i = 0; i < size; i++){
        array[i] = ob.array[i];
    }
   
}
*/
/*
stack::~stack(){
    delete [] array;
}  */

bool stack::isEmpty(){
    return topElem == -1;
}


int stack::push(int a){
    if (topElem == SIZE-1){
        cout << "Стэк заполнен!";
        return 0;
    }
    topElem++;
    size++;
    array[topElem] = a;
    return 1;
}

void stack::pop(){
    if (topElem == -1){
        cout << "Стэк пуст!"; exit(1);
        //return NULL;
    }
    topElem--;
    size--;
}

int stack::top(){
    if (topElem == -1){
        cout << "Стэк пуст"; exit(1);
        //return;
    }
    return array[topElem];
}

int stack::pop2(){
    if (topElem == -1){
        cout << "Стэк пуст"; exit(1);
    }
    int a = top();
    pop();
    return a;
}

bool stack::isOne(){
    if (topElem == 0)
        return true;
    else 
        return false;
}


int isDigit(char* str){
    if (((str[0] == '-' || str[0] == '+') && strlen(str)>1) || isdigit(str[0])){
       for (int i = 1; i < strlen(str) ; i++){
            if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
    }
    else 
        return 0;
} 

int postfix(stack* obj, ifstream& stream){
    int res;
    char buf[30];
  while(stream>>buf) {
        //cin >> buf; 
     if (isDigit(buf)){
        res = atoi(buf);
        obj->push(res);
        cout << "\nПоложили число: " << atoi(buf);
     } 
     if (strlen(buf) == 1 && buf[0] == '+'){
        if (obj->isOne() || obj->isEmpty()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        res = obj->pop2() + obj->pop2();
        obj->push(res);
     }
     if (strlen(buf) == 1 && buf[0] == '*'){
        if (obj->isOne() || obj->isEmpty()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        res = obj->pop2() * obj->pop2();
        obj->push(res);
     }
     if (strlen(buf) == 1 && buf[0] == '-')  {  
        if (obj->isOne() || obj->isEmpty()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        int a = obj->pop2();
        res = obj->pop2() - a;
        obj->push(res);
     } 
     if (strlen(buf) == 1 && buf[0] == '^')  {  
        if (obj->isOne() || obj->isEmpty()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        int a = obj->pop2();
        res = pow(obj->pop2(), a);
        obj->push(res);
     }
     if (strlen(buf) == 1 && buf[0] == '/')  {  
        if (obj->isOne() || obj->isEmpty()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        int a = obj->pop2();
        res = obj->pop2()/a;
        obj->push(res);
     }
     if (!isDigit(buf) && strlen(buf) > 1)
       cout << "\nОшибка! Встречан некорректный символ";
    }
    res = obj->pop2();
    return res;
}

void fixed(){
    cin.clear(); 
    while (cin.get() != '\n');
}

void toLower(string &str){
    int i = 0;
    while (str[i]){
        str[i] = tolower(str[i]);
        i++;
    }
}


/*
int stack::topelem(){
    return topElem;
}
*/


int main()
{
    string str;
    stack* obj;
   // char* buf = new char[50];
    int res = 0;
    int a;
    obj = new stack;
  
do{
    delete obj;
    obj = new stack;
    char* buf = new char [256];
    int res = 0;
    cout << "Считать из файла - \033[1;34m\'f\' , \033[0m или с консоли - \033[1;34m\'c\': \033[0m";
    cin >> str; toLower(str);
    while (str!=file && str!=con)
      {
        cout << "\033[1;31mОшибка ввода, попробуйте снова: \033[0m" ;
        cin >> str;
     }
    
  if (str == file)
       {
         string fileName;  
         cout << "\033[0;32mВведите имя файла:\033[0m ";
         cin >> fileName;
         ifstream in(fileName.c_str(),ios::in | ios::binary);
         while(!in)
           {
             cout <<"\033[1;31mНе удается открыть файл.Введите корректное имя: \033[0m";
             cin >> fileName;
             in.open(fileName.c_str(),ios::in | ios::binary);
            }
          res = postfix(obj, in);
       }
    
    
  else {
      cout << "\033[0;32mВведите выражение в постфиксной форме:\033[0m ";
      fixed();
      
      
    while(cin.peek() != '\n') {
        cin >> buf; 
     if (isDigit(buf)){
        a = atoi(buf);
        obj->push(a);
        cout << "\nПоложили в стэк: \033[0;32m" << atoi(buf) << "\033[0m";
     } 
     if (strlen(buf) == 1 && buf[0] == '+'){
        if (obj->isOne() || obj->isEmpty()){
            cout << "\n\033[1;31mОшибка! В стэке не хватает чисел!\033[0m"; exit(1);
        }
        cout <<"\nВстречан символ \033[1;34m\'+\'\033[0m, ";
        res = obj->pop2() + obj->pop2();
        obj->push(res);
        cout << "положили результат суммы \033[0;32m"<< obj->top();
     }
     if (strlen(buf) == 1 && buf[0] == '*'){
        if (obj->isOne() || obj->isEmpty()){
            cout << "\n\033[1;31mОшибка! В стэке не хватает чисел!"; exit(1);
        }
        cout <<"\nВстречан символ \033[1;34m\'*\'\033[0m, ";
        res = obj->pop2() * obj->pop2();
        obj->push(res);
        cout << "положили результат умножения \033[0;32m"<< obj->top() << "\033[0m";
     }
     if (strlen(buf) == 1 && buf[0] == '-')  {  
        if (obj->isOne() || obj->isEmpty()){
            cout << "\n\033[1;31mОшибка! В стэке не хватает чисел!"; exit(1);
        }
        cout <<"\nВстречан символ \033[1;34m\'-\'\033[0m, ";
        int a = obj->pop2();
        res = obj->pop2() - a;
        obj->push(res);
        cout << "положили результат разности \033[0;32m"<< obj->top() << "\033[0m";
     } 
     if (strlen(buf) == 1 && buf[0] == '^')  {  
        if (obj->isOne() || obj->isEmpty()){
            cout << "\n\033[1;31mОшибка! В стэке не хватает чисел!"; exit(1);
        }
        cout <<"\nВстречан символ \033[1;34m\'^\'\033[0m, ";
        int a = obj->pop2();
        res = pow(obj->pop2(), a);
        obj->push(res);
        cout << "положили результат возведения в степень \033[0;32m"<< obj->top() << "\033[0m";
     }
     if (strlen(buf) == 1 && buf[0] == '/')  {  
        if (obj->isOne() || obj->isEmpty()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        cout <<"\nВстречан символ \033[1;34m\'/\'\033[0m, ";
        int a = obj->pop2();
        res = obj->pop2()/a;
        obj->push(res);
        cout << "положили результат возведения в целочисленного деления \033[0;32m"<< obj->top() << "\033[0m";
     }
     if (!isDigit(buf) && strlen(buf) > 1)
       cout << "\n\033[1;31mОшибка! Встречан некорректный символ";
    }
    res = obj->pop2();
  } // else  
    cout <<"\n\nРезультат: " << res;
    
    cout << "\n" << "Вы хотите продолжить \033[1;34m[y/n]\033[0m ? : ";
    cin >> str;
    toLower(str);
    while (str!=stop && str!=again){
        cout << "\n\033[1;31mОшибка, введите [y/n] :\033[0m";
        cin >> str; toLower(str);
    }
    cout << "\n"; step = 1;    
    
 delete [] buf;   
}while(str != "n");    
    return 0;
}
