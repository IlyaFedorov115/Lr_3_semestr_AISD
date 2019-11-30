#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <chrono>


using namespace std;

string file = "f";
string con = "c";
string stop = "n";
string again = "y";


class Node{                           //класс узла дерева
   public:
	 int a;
	 char c;
	 Node *left;                       //левое и правое
	 Node *right;                      //поддеревья
	 Node(){
	     left = NULL;
	     right = NULL;
	 }

	 Node(Node *L, Node *R) { 
	    a = 0;
	    left =  L; if(left) a += L->a;
	    right = R; if(right) a += L->a;
	   // a = L->a + R->a; 
	 }
};


struct MyCompare
{
    bool operator()(const Node* l, const Node* r) const { 
        return l->a < r->a; 
    }
};


vector<bool> code;                
map<char,vector<bool> > table;    

void BuildTable(Node *root){                                //каждому символу сопоставляем полученный код хаффмана 	
    if (root->left!=NULL){                                  // это таблица table
        code.push_back(0);
        BuildTable(root->left);
    }
     
    if (root->right!=NULL){                                //если вправо, то единицу
        code.push_back(1);                                 //code - накапливается
        BuildTable(root->right);
    }
    if (root->left==NULL && root->right==NULL) {
        if (code.empty()) code.push_back(0);
        table[root->c] = code;
    }
    code.pop_back();                                         //шаг назад
}




//////////////////////////////////////////////////////////// 

Node* makeTree(list<Node*> &t){
   if (t.size() == 0) { cout<< "\n\x1b[1;31mError!! Элементов нет."; exit(1);} 
   if (t.size() == 1) {
      Node *sonL = t.front(); t.pop_front();
      Node *parent = new Node(sonL, NULL); t.push_back(parent);
   }
   while (t.size()!=1){  
     t.sort(MyCompare());
    
     Node *SonL = t.front();
     t.pop_front();
     Node *SonR = t.front(); 
     t.pop_front();
     
     Node *parent = new Node(SonL,SonR); 
     t.push_back(parent);

  }
  return t.front();	
}

/////////////////////////////////////

#include "print.h"
#include "readCode.h"



Node* haffmanCoder(ifstream &f, char* output, int &countStep, int &countSymbol){
    map<char,int> period; map<char,int>::iterator i;              //считываем из файла и заносим частоту 
    int k = 0;
    cout << "\n\x1b[1;32mЧастоты встречаемости символов: \x1b[0m\n";
    while (!f.eof()){                
	    char c = f.get();            
	    if (c == EOF)
	      continue;
	    period[c]++; countSymbol++;
	}
/*	//вывод полученных частот встречаемости  если че, то создать глобальный
    for (i = period.begin(); i != period.end(); ++i, k++){
        if (k == 3) { k = 0; cout << "\n"; }
        cout <<"\'"<< i->first << "\'" <<" -- "<< i->second<< "\t";
    }
    cout << "\n\n";  */
    
    list<Node*> lst;              // список частот для сортировки в алгоритме
    map<char,int>::iterator j;
    for (j = period.begin(); j != period.end(); ++j){               //создаем список символов с их частотой
        Node *p = new Node;                                        //для сортировки 
        p->c = j->first;
        p->a = j->second;
        lst.push_back(p);                                             //добавить в конец
    }
    /// Node* makeTree(list<Node*> &t){
    //////  создаем дерево
    
    if (t.size() == 0) { cout<< "\n\x1b[1;31mError!! Элементов нет."; exit(1);} 
    if (t.size() == 1) {
       Node *sonL = t.front(); t.pop_front();
       Node *parent = new Node(sonL, NULL); t.push_back(parent);
    }
    while (t.size() != 1){
        
      t.sort(MyCompare());
    
      Node *SonL = t.front();
      t.pop_front();
      Node *SonR = t.front(); 
      t.pop_front();
     
      Node *parent = new Node(SonL,SonR); 
      t.push_back(parent);  countStep++;
     }
     Node* root = t.front();                  //можно вывести
     
     ////// создаем пары 'символ-код':			
   	 BuildTable(root);                        //можно вывести коды
   	 
     f.clear(); f.seekg(0);                   // перемещаем указатель снова в начало файла
    
     ofstream g(output, ios::out | ios::binary);	
     int count = 0; char buf = 0;
     while (!f.eof()){ 
       char c = f.get();  //if(c == EOF) continue;
	   vector<bool> x = table[c];
	   for(int n = 0; n < x.size(); n++){
	     buf = buf | x[n] << (7-count);   
	     count++;   
	     if (count == 8) { count = 0;   g << buf; buf = 0; } 
          }
     }
     
    f.close();  g.close(); 
}





void decoder(ifstream &F, Node* root = NULL){
   if (root == NULL){
      readBytefile(F);
      root = maketreeCode();
      printCode();
   }
	  Node *p = root; 
	  int step = 1;
	  vector<char> str,result,acc;
	  str.push_back(' ');
      while(!F.eof()){    //!feof(F)
        char ch = F.get();
        if (ch == '1'){
		    p = p->right;
		    if (p == NULL) { cout<<"\n\x1b[1;31mОшибка! Неверное кодирование!"; exit(1);}
        } 
		else if (ch == '0') {
		    p = p->left;
		    if (p == NULL) { cout<<"\n\x1b[1;31mОшибка! Неверное кодирование!"; exit(1);}
		}
		else if (ch == ' ' || ch == '\n')
	        continue;
	    else if (ch == EOF)
	        break;
	    else{
	       cout << "\n\x1b[1;31mОшибка!! Неправильное кодирование сообщения!"; exit(1);
	    }
	    acc.push_back(ch);    

		 if (p->left == NULL && p->right == NULL && (p->c)) {
		    cout <<"\n\x1b[1;34m"<<step++<<")\x1b[0m шаг: ";
		    printVect(str,1); printVect(acc,0);
		    cout << "\nДекодирован: \x1b[1;36m\'"<< p->c <<"\'\x1b[0m";
		    pushVector(str,acc);
		    acc.clear(); result.push_back(p->c);
		    p = root;
		}
          
      } ////
   cout << "\n\x1b[5;1;34mРаскодированное сообщение: \x1b[0m";
 //  deleteTree(root);
  // printVect(result,1);
}




///////////////////////////////////////////////////////////////
int main (){
  string strEnd;    
     
do{
     

/////// Часть про кодирование и декодирование Хаффмана
    
    
    auto start = chrono::high_resolution_clock::now();
    
    
    
    auto end = chrono::high_resolution_clock::now();
    chrono::durarion<float> durarion = end - star;
    cout << durarion.count();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
 //////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "\n" << "Вы хотите продолжить \033[1;34m[y/n]\033[0m ? : ";
    cin >> strEnd;
    toLower(strEnd);
    while (strEnd!=stop && strEnd!=again){
        cout << "\n\033[1;31mОшибка, введите [y/n] :\033[0m";
        cin >> strEnd; toLower(strEnd);
    } 
   f.close();
   map<char,vector<bool> >::iterator il;
   for (auto it = table.begin(); it != table.end(); ++it)
   {
     table.erase(it->first);
   }
    code.clear();
   
 }while(strEnd != "n");
	return 0;
}
