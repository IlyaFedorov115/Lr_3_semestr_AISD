#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define SIZE 500


class stack{
  private:
    int array[SIZE];
    int topElem;
    int size;
  public:
    stack();
    //stack(const stack &ob);
   // ~stack();
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
    int size = 0;
    int topElem = -1;
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
    if (topElem == size-1){
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

/*
int postfixCalc(stack& obj,istream &stream){
    int a = 0;
    char buf[256];
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
}
*/



int main()
{
    stack obj;
    cout << "LOL\n";
    char buf[256];
    int res = 0;
    int a;
    do {
        cin >> buf; 
     if (isDigit(buf)){
        a = atoi(buf);
        obj.push(a);
        cout << "\nПоложили число: " << atoi(buf);
     } 
     if (strlen(buf) == 1 && buf[0] == '+'){
        if (obj.isOne()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        res = obj.pop2() + obj.pop2();
        obj.push(res);
     }
     if (strlen(buf) == 1 && buf[0] == '*'){
        if (obj.isOne()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        res = obj.pop2() * obj.pop2();
        obj.push(res);
     }
     if (strlen(buf) == 1 && buf[0] == '-')  {  
        if (obj.isOne()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        int a = obj.pop2();
        res = obj.pop2() - a;
        obj.push(res);
     } 
     if (strlen(buf) == 1 && buf[0] == '^')  {  
        if (obj.isOne()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        int a = obj.pop2();
        res = pow(obj.pop2(), a);
        obj.push(res);
     }
     if (strlen(buf) == 1 && buf[0] == '/')  {  
        if (obj.isOne()){
            cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
        }
        int a = obj.pop2();
        res = obj.pop2()/a;
        obj.push(res);
     }
     if (!isDigit(buf) && strlen(buf) > 1)
       cout << "\nОшибка! Встречан некорректный символ";
    }while(cin.peek() != '\n');
    res = obj.pop2();
    cout <<"\n\n\n\n" << res;
    return 0;
}
