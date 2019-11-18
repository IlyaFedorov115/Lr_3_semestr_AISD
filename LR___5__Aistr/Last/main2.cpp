#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>


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

void BuildTable(Node *root){         //каждому символу сопоставляем полученный код хаффмана 	
    if (root->left!=NULL){           // это таблица table
        code.push_back(0);
        BuildTable(root->left);
    }
     
    if (root->right!=NULL){                       //если вправо, то единицу
        code.push_back(1);                        //code - накпливается
        BuildTable(root->right);
    }
   //if root->c
    if (root->left==NULL && root->right==NULL) {
        if (code.empty()) code.push_back(0);
        table[root->c] = code;
    }
    code.pop_back();                              //шаг назад
}





void printTree(Node* root, int k){          // вывод дерева 
    if (root != NULL){
        printTree(root->left, k+3);
        for (int i = 0; i < k; i++)
            cout << "  ";
            
        if (root->c)  
            cout << root->a << '(' << root->c << ')' << endl;
        
        else 
            cout << root->a << endl;
        printTree(root->right, k+3);    
    }
}



//////////////////////////////////////////////////////////// МОИ ФУНКЦИИИ

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

void printVect(vector<char> &p, int flag){
    if(flag){
    for (int i = 0; i < p.size(); i++)
        cout << p[i];
    }
    else {
       for (int i = 0; i < p.size(); i++)
          cout <<"\x1b[1;4;33m"<< p[i];
    }
    cout<<"\x1b[0m";
}

void pushVector(vector<char> &a, vector<char> &b){
    for (int i = 0; i < b.size(); i++)
        a.push_back(b[i]);
}

/////////////////////////////////////
void readCodefile(ifstream& f);
Node* makeNode(map<char,vector<bool> >::iterator &ii,int k);
void makeNode_(map<char,vector<bool> >::iterator &ii, int k, Node* tmp);
Node* maketreeCode();




void printCode(){
    int k = 0;
    cout << "\n\x1b[1;32mКоды символов для данного текста: \x1b[0m\n";
    map<char,vector<bool> >::iterator ii;
    for (ii = table.begin(); ii != table.end(); ++ii, k++){
        if (k == 3) { k = 0; cout << "\n";}
        char c = ii->first;
        cout <<"\'" <<c <<"\'" << " - ";
        vector<bool> x = table[c];
        for (int i = 0; i < x.size(); i++)
            cout << x[i];
        cout << "\t";    
    }
    cout <<"\n";
}



void printCrypt(ifstream& f){
    f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла
	ofstream outF("output.txt", ios::out | ios::binary);
    
    cout <<"\n\x1b[1;32mЗакодированное сообщение: \x1b[0m";	
    int count = 0; char buf = 0;
    while (!f.eof()){ 
      char c = f.get();                //считываем символ
	  vector<bool> x = table[c];
	  for(int i = 0; i < x.size(); i++){
	    cout << x[i];
	    outF << x[i];
	  }
    }
    outF.close();
}


void period(ifstream& f, map<char,int> &m){
    int k = 0;
    cout << "\n\x1b[1;32mЧастоты встречаемости символов: \x1b[0m\n";
    while (!f.eof()){                //считываем из файла и заносим частоту 
	   char c = f.get();            //  getc getch
	   if (c == EOF)
	     continue;
	   m[c]++;
	}
	map<char,int>::iterator i;                  //вывод полученных частот встречаемости
    for (i = m.begin(); i != m.end(); ++i, k++){
        if (k == 3) { k = 0; cout << "\n"; }
        cout <<"\'"<< i->first << "\'" <<" -- "<< i->second<< "\t";
    }
    cout << "\n\n";
}


void makeList(list<Node*> &lst, map<char,int> &occur){
     map<char,int>::iterator i;
     for (i = occur.begin(); i != occur.end(); ++i){           //создаем список символов с их частотой
        Node *p = new Node;                           //для сортировки 
        p->c = i->first;
        p->a = i->second;
        lst.push_back(p);                    //добавить в конец
    }
}



void toLower(string &str){
    int i = 0;
    while (str[i]){
        str[i] = tolower(str[i]);
        i++;
    }
}

void deleteTree(Node *root){
    if (root->left)
        deleteTree(root->left);
    if (root->right)    
        deleteTree(root->right);
    delete root;  ////////////////////////////ERROR??  
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

#include "readCode.h"

void decoder(ifstream &F, Node* root = NULL){
   if (root == NULL){
    // readCodefile(F);
      readBytefile(F);
      root = maketreeCode();
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
/*	    if (((p->left == NULL || p->right == NULL) && !(p->c)) || ((p->left == NULL || p->right == NULL) && (p->c))) 
	        cout << "Неверный вид кодирования!!";  */
        //str.push_back(ch);
          
      } ////
   cout << "\n\x1b[5;1;34mРаскодированное сообщение: \x1b[0m";
   printVect(result,1);
}


void printDialog(){
    cout << "\n\x1b[1;32mВыберите способ работы:\x1b[0m";
    cout << "\n\x1b[1;33m\'1\'\x1b[0m -- Прочитать файл с сообщением, закодировать его\n\tи раскодировать это же сообщение.\n";
    cout << "\x1b[1;33m\'2\'\x1b[0m -- Прочитать файл с \x1b[4mзакодированным\x1b[0m сообщением и раскодировать его\n\t(в начале файла указаны частоты символов).\n";
    cout << "\x1b[1;33m\'3\'\x1b[0m -- Прочитать файл с \x1b[4mзакодированным\x1b[0m сообщением и раскодировать его\n\t(в начале файла указаны коды символов).\n";
    cout << "выбор:";
}

///////////////////////////////////////////////////////////////
int main (int argc, char *argv[]){
  string strEnd;    
     
do{
     
     printDialog();
     cin >> strEnd;
     while (strEnd != "1" && strEnd!= "2" && strEnd != "3"){
        cout << "\n\033[1;31mОшибка, введите [1/2/3]: \033[0m";
        cin >> strEnd; 
     } 
      
     string fileName;  
     cout << "\x1b[1;32m\nВведите имя файла:\x1b[0m ";
     cin >> fileName;
     
     ifstream f(fileName.c_str(),ios::in | ios::binary);
     while(!f) {
        cout <<"\033[1;31m\nНе удается открыть файл.Введите корректное имя: \033[0m";
        cin >> fileName;
        f.open(fileName.c_str(),ios::in | ios::binary);
     }
    
    
  if (strEnd == "1"){
        map<char,int> occur; map<char,int>::iterator i;
    	period(f,occur);                              //считываем периодичность
        list<Node*> lst;
        makeList(lst,occur);
        Node* root = makeTree(lst);
  //    printTree(root,1);
        BuildTable(root);                         //заполняем table кодами хаффмана для символов
        printCode();  printCrypt(f); 
       // f.close();
    	ifstream file("output.txt", ios::in | ios::binary);
    	if(file.eof())
	        cout << "\x1b[1;31mФайл пуст!! Декодировать нечего!!\x1b[0m"; 
    	else {
    	    decoder(file,root);
            file.close();	deleteTree(root);
	     }
  }
  
  else if (strEnd == "2"){
      map<char,int> occur; map<char,int>::iterator i;
      readCodefile(f,occur);
      list<Node*> lst;
      makeList(lst,occur);
      Node* root = makeTree(lst);
      decoder(f,root); deleteTree(root);
  }
    
  else{
      decoder(f); deleteTree(root);////???
   }  
    
    cout << "\n" << "Вы хотите продолжить \033[1;34m[y/n]\033[0m ? : ";
    cin >> strEnd;
    toLower(strEnd);
    while (strEnd!=stop && strEnd!=again){
        cout << "\n\033[1;31mОшибка, введите [y/n] :\033[0m";
        cin >> strEnd; toLower(strEnd);
    } 
   f.close();
   map<char,vector<bool> >::iterator il;
  // table.clear();
for (auto it = table.begin(); it != table.end(); ++it)
{
    table.erase(it->first);
  // cout << (*it).first << " : " << (*it).second << endl;
}
      
  }while(strEnd != "n");
	return 0;
}
