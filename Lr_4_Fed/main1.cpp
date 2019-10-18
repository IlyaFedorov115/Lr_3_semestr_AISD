/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;



typedef struct node {  // структура элемента очереди
    union type1 {
      int elem;
      char data;
    }type;
    struct node* next;
    struct node* prev;
}node;
typedef node* pNode;

typedef struct Queue{
    pNode head, tail;
}Queue;

void pushTail(Queue &obj, char x){
    pNode newNode;
    newNode = new node;   // создать новый узел
    newNode->type.data = x;    //добавить в новый узел элемент
    newNode->prev = obj.tail;   //теперь в хвосте новый элемент
    newNode->next = NULL;
    if (obj.tail)     // добавить узел в конец очереди
        obj.tail->next = newNode;
    obj.tail = newNode;
    if (!obj.head)
        obj.head = obj.tail;        //если это первый элемент
}



char popHead(Queue &obj){
    pNode top = obj.head;
    char x;
    if (top == NULL){   //очерель пуста
           cout << "\nОчередь пуста!!!";
           exit(1);
    }
    x = top->type.data;       //запомнить первый элемент
    //obj.head = top->next;
    obj.head = obj.head->next;
    if (obj.head == NULL)     // если в очереди ничего нет
        obj.tail = NULL;
    delete top;
    return x;
}








void printQueue(Queue &obj){
    pNode tmp = obj.tail;
    cout << "\n ";
    while (tmp){
        cout << tmp->type.data << " "; 
        tmp = tmp->prev;
    }
}


int main()
{
    cout<<"Hello World\n";
    Queue obj;
    obj.tail = NULL;
    obj.head = NULL;
    pushTail(obj, 'a');
    pushTail(obj, 'b');
    pushTail(obj, 'c');
    pushTail(obj, 'd');
    pushTail(obj, 'e');
    pushTail(obj, 'f');
    printQueue(obj);
popHead(obj);
   //cout <<"\n pop = "<< a;
    printQueue(obj);
    return 0;
}
