#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;
#define SIZE 500


class stack{
  private:
    int* array;
    int topElem;
    int size;
  public:
    stack(int maxsize = SIZE);
    stack(const stack &ob);
    ~stack();
    bool isEmpty();
    int push(int a)
    int pop();
    int top();
    int pop2();
    bool isOne();
 
};


stack::stack(int maxsize = SIZE){
    array = new int [maxsize];
    int size = maxsize;
    int topElem = -1;
}

stack::stack(const stack &ob){
    int size = ob.size;
    int topElem = ob.topElem;
    array = new int [size];
    for (int i = 0; i < size; i++){
        array[i] = ob.array[i];
    }
   
}


stack::~stack(){
    delete [] array;
}

bool stack::isEmpty(){
    return topElem == -1;
}


int stack::push(int a){
    if (topElem = size-1){
        cout << "Стэк заполнен!";
        return 0;
    }
    topElem++;
    array[topElem] = a;
    return 1;
}

int stack::pop(){
    if (topElem == -1){
        cout << "Стэк пуст!"; exit(1);
        //return NULL;
    }
    topElem--;
}

int stack::top(){
    if (topElem == -1){
        cout << "Стэк пуст"; exit(1);
        return;
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


int postfixCalc(stack& obj,istream &stream){
    
}

int main()
{
    cout<<"Hello World";

    return 0;
}
