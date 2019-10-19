/******************************************************************************
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <iostream>

using namespace std;



template <typename Qtype> class node {  // структура элемента очереди
   public:
    Qtype data;
    node<Qtype>* next;
    node<Qtype>* prev;
    node() { next = prev = NULL;}
};
//typedef node* pNode;

template <typename Qtype> class Queue{
    node<Qtype> *head;
    node<Qtype> *tail;
  public:
    Queue() { head = tail = NULL;}
    void pushTail(Qtype x);
    Qtype popHead();
    void printQueue();
};

template <typename Qtype>
void Queue<Qtype>::pushTail(Qtype x){
    node<Qtype>* newNode;
    newNode = new node<Qtype>;   // создать новый узел
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
    node<Qtype>* top = head;
    Qtype x;
    if (top == NULL){   //очерель пуста
           cout << "\nОчередь пуста!!!";
           exit(1);
    }
    x = top->data;       //запомнить первый элемент
    //obj.head = top->next;
    head->next->prev = NULL;
    head = head->next;
    if (head == NULL)     // если в очереди ничего нет
        tail = NULL;
    delete top;
    return x;
}







template <typename Qtype>
void Queue<Qtype>::printQueue(){
    node<Qtype>* tmp = this->tail;
    cout << "\n ";
    if (tmp == NULL){
        cout << "PESTO"; return;
    }
    while (tmp != NULL){
        cout << tmp->data << " "; 
        tmp = tmp->prev;
    }
}


int main()
{
    cout<<"Hello World\n";
    Queue<char> obj; 
    obj.pushTail( 'a');
    obj.pushTail( 'b');
    obj.pushTail( 'c');
    obj.pushTail( 'd');
    obj.pushTail( 'e');
    obj.pushTail( 'f');
    obj.printQueue();
obj.popHead();
   //cout <<"\n pop = "<< a;
    obj.printQueue();
    
    
    
    Queue<int> obj2; 
    obj2.pushTail( 1);
    obj2.pushTail( 2);
    obj2.pushTail( 3);
    obj2.pushTail(4);
    obj2.pushTail( 5);
    obj2.pushTail( 6);
    obj2.printQueue();
obj2.popHead();
   //cout <<"\n pop = "<< a;
    obj2.printQueue();
    
    
     Queue<float> obj23; 
    obj23.pushTail( 1.1);
    obj23.pushTail( 2.2);
    obj23.pushTail( 1.3);
    obj23.pushTail(4.5);
    obj23.pushTail( 5.4);
    obj23.pushTail( 6.2);
    obj23.printQueue();
obj23.popHead();
obj23.popHead();
obj23.popHead();
obj23.popHead();
obj23.popHead();
obj23.popHead();
   //cout <<"\n pop = "<< a;
    obj23.printQueue();
    return 0;
}
