/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
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
      Item pop()
        { return s[--N]; }
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

stack* stack::pop(){
    if (topElem == -1){
        cout << "Стэк пуст!";
        return NULL;
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




int main()
{
    cout<<"Hello World";

    return 0;
}
