
#include <iostream>
#include <fstream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;


template <typename Qtype> class node1 {  // структура элемента очереди
   public:
    Qtype data;
    node1<Qtype>* next;
    node1<Qtype>* prev;
    node1() { next = prev = NULL;}
};
//typedef node* pNode;

template <typename Qtype> class Queue{
    node1<Qtype> *head;
    node1<Qtype> *tail;
  public:
    Queue() { head = tail = NULL;}
    void pushTail(Qtype x);
    Qtype popHead();
    void printQueue();
    bool empty();
};




template <typename Qtype>
void Queue<Qtype>::pushTail(Qtype x){
    node1<Qtype>* newNode;
    newNode = new node1<Qtype>;   // создать новый узел
    newNode->data = x;    //добавить в новый узел элемент
    newNode->prev = tail;   //теперь в хвосте новый элемент
    newNode->next = NULL;
    if (tail != NULL)     // добавить узел в конец очереди
        tail->next = newNode;
    tail = newNode;
    if (!head)
        head = tail;        //если это первый элемент
}


template <typename Qtype>
Qtype Queue<Qtype>::popHead(){
    node1<Qtype>* top = head;
    Qtype x;
    if (top == NULL){   //очерель пуста
           cout << "\nОчередь пуста!!!";
           exit(1);
    }
    x = top->data;       //запомнить первый элемент
    //obj.head = top->next;
  //  head->next->prev = NULL;
    head = head->next;
    if (head == NULL)     // если в очереди ничего нет
        tail = NULL;
    delete top;
    return x;
}

template <typename Qtype>
bool Queue<Qtype>::empty(){
      return head == NULL;
}


template <typename Qtype>
void Queue<Qtype>::printQueue(){
    node1<Qtype>* tmp = this->tail;
    cout << "\n ";
    if (tmp == NULL){
        cout << "PESTO"; return;
    }
    while (tmp != NULL){
        cout << tmp->data << " "; 
        tmp = tmp->prev;
    }
}
