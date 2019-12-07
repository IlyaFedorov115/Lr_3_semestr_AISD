#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <ctime>
#include <chrono>
#include <algorithm>  // sort
using namespace std;


string file = "f";
string con = "c";
string stop = "n";
string again = "y";
int flag=0;

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


struct MyCompare2
{
    bool operator()(const Node* l, const Node* r) const { 
        return l->a > r->a; 
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
    if (!code.empty())
       code.pop_back();                                         //шаг назад
}



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



Node* haffmanCoder(ifstream &f, const char* output, int &countStep, int &countSymbol){
    map<char,int> period; map<char,int>::iterator i;              //считываем из файла и заносим частоту 
    int k = 0;
    while (!f.eof()){                
	   char c = f.get();            
	   if (c == EOF)
	      continue;
	    period[c]++;
	}

    list<Node*> lst;              // список частот для сортировки в алгоритме
    map<char,int>::iterator j;
    for (j = period.begin(); j != period.end(); ++j){               //создаем список символов с их частотой
        Node *p = new Node;                                        //для сортировки 
        p->c = j->first;
        p->a = j->second;
        lst.push_back(p);                                             //добавить в конец
    }

    
    if (lst.size() == 0) { cout<< "\n\x1b[1;31mError!! Элементов нет."; exit(1);} 
    if (lst.size() == 1) {
       Node *sonL = lst.front(); lst.pop_front();
       Node *parent = new Node(sonL, NULL); lst.push_back(parent);
    }
    while (lst.size() != 1){
      countStep++; 
      lst.sort(MyCompare());
    
      Node *SonL = lst.front();
      lst.pop_front();
      Node *SonR = lst.front(); 
      lst.pop_front();
     
      Node *parent = new Node(SonL,SonR); 
      lst.push_back(parent);  countStep++;
     }
     Node* root = lst.front();          
     
   	 BuildTable(root);                        
   	 
     f.clear(); f.seekg(0);                   // перемещаем указатель снова в начало файла
    
     ofstream g(output, ios::out | ios::binary);	
     int count = 0; char buf = 0;
     while (!f.eof()){ 
      unsigned char c = f.get();  //if(c == EOF) continue;
	   vector<bool> x = table[c];
	   for(int n = 0; n < x.size(); n++){
	     buf = buf | x[n] << (7-count);   
	     count++; countSymbol++;
	     if (count == 8) { count = 0;   g << buf; buf = 0; } 
          }
     }
     if (count != 0) g << buf;
    f.close();  g.close(); 
    return root;
}



void decoder(ifstream &F, const char* outFile, int &countStep,int &countSymbol, Node* root = NULL){
   if (root == NULL){
      readBytefile(F);
      root = maketreeCode();
    }
    Node *p = root;
	int count = 0; char byte; 
	byte = F.get();
	ofstream g(outFile, ios::out | ios::binary);
	while(!F.eof() && countSymbol != 0){ 
	    countStep++; countSymbol--;
	    bool b = byte & (1 << (7-count) ); 
		if (b){
		   p = p->right;
		   if (flag) cout << 1;
		}
		else{
		   p = p->left;
		   if (flag) cout << 0;
		}
	   if (p->left == NULL && p->right == NULL) {
		     g << p->c; 
		     p = root; 
		}  
		count++;
		if (count == 8) {
		  count = 0;  
		  byte = F.get();
		}
	}

}



int stepMid = 0;
//глобальные SL и SR
int Middle(vector<Node*> &wperiod, int S, int B, int &SL, int &SR){
    stepMid++;
    float D;  int k = B;
    SL = wperiod[k]->a; SR = S - SL; D = SL - SR;
    while ((D + wperiod[k+1]->a) < 0){
        k = k + 1;
        SL = SL + wperiod[k]->a;
        SR = SR - wperiod[k]->a;
        D = SL - SR;
    }
    return k;
}


int stepF_Sh = 0;

Node* F_Sh(vector<Node*> &wperiod, int S, int B, int E, vector<bool> code){
    stepF_Sh++;
    if (B == E){
    	if (B == 0 && stepF_Sh == 1){
    	  code.push_back(0);
    	}
        table[wperiod[B]->c] = code;
        return wperiod[B];
    }
    int SL, SR, k;
    k = Middle(wperiod, S, B, SL, SR);
    code.push_back(0);
    Node* bL = F_Sh(wperiod, SL, B, k, code);
    code.pop_back(); code.push_back(1);
    Node* bR = F_Sh(wperiod, SR, k+1, E,code);
    Node* b = new Node(bL, bR);
    return b;
}



Node* FanoSh(ifstream &f, const char* output, int &countStep, int &countSymbol){
    map<char,int> period; map<char,int>::iterator i;               
    int k = 0;
    while (!f.eof()){                
	   char c = f.get();            
	   if (c == EOF)
	      continue;
	    period[c]++;
	}
	
    vector<Node*> wperiod;
    map<char,int>::iterator j;
    for (j = period.begin(); j != period.end(); ++j){               //создаем список символов с их частотой
        Node *p = new Node;                                        //для сортировки 
        p->c = j->first;
        p->a = j->second;
        //stepF_Sh++;
        wperiod.push_back(p);                                             //добавить в конец
    }


    sort(wperiod.begin(), wperiod.end(), MyCompare());
    int S = 0; int E = 0; 
    vector<bool> Code;
    for(int i = 0; i < wperiod.size(); ++i){
        S += wperiod[i]->a;
        E++;
    }
    E--;
    Node* root = F_Sh(wperiod, S, 0, E, Code);
    if (E == 0) {
    	Node* tmp = new Node;
    	tmp->left = root;
    	root = tmp;
    }  
   // BuildTable(root);                        //можно вывести коды
   	 
     f.clear(); f.seekg(0);                   // перемещаем указатель снова в начало файла
    
     ofstream g(output, ios::out | ios::binary);	
     int count = 0; char buf = 0;
     while (!f.eof()){ 
      unsigned char c = f.get();  //if(c == EOF) continue;
	   vector<bool> x = table[c];
	   for(int n = 0; n < x.size(); n++){
	     buf = buf | x[n] << (7-count);   
	     count++;  countSymbol++;
	     if (count == 8) { count = 0;   g << buf; buf = 0; } 
          }
     }
    if (count != 0) g << buf;
    f.close();  g.close(); 
    return root;

}




///////////////////////////////////////////////////////////////
int main (){
    
  string strEnd;   
  int sizef = 0; 
  int countStep = 0;
  int countSymbol = 0;
  long sizeFile = 0;
  string choice;
  Node* root;     
do{
    
     printDialog();
     cin >> strEnd;
     while (strEnd != "1" && strEnd != "2"){
        cout << "\n\033[1;31mОшибка, введите [1/2]: \033[0m";
        cin >> strEnd; 
     } 
    

    printDialog1();
    cin >> choice;
    while (strEnd != "1" && strEnd != "2"){
        cout << "\n\033[1;31mОшибка, введите [1/2]: \033[0m";
        cin >> choice; 
     }
/////// Часть про кодирование и декодирование Хаффмана
     string fileName;
    
   ifstream file; 
   if (choice == "1"){    
     cout << "\x1b[1;32m\nВведите имя файла:\x1b[0m ";
     cin >> fileName;
     
     file.open(fileName.c_str(), ios::in | ios::binary);
     while(!file) {
        cout <<"\033[1;31m\nНе удается открыть файл.Введите корректное имя: \033[0m";
        cin >> fileName;
        file.open(fileName.c_str(),ios::in | ios::binary);
     }   
}
   
   else{
      int len = -1;
      while (len < 0){
   	      cout << "\nВведите длину: ";
          cin >> choice; len = atoi(choice.c_str());
          if (len == 0) {cout << "\nПустой файл!"; return 0;}
          if (len < 0) 
             cout << "\nОшибка!! Некорректное число.";
       }
      fileName = "randText.txt";
      randomText(len,fileName.c_str(),0);
      file.open(fileName.c_str(),ios::in | ios::binary);
   }


   string outFile; 
   if (file.eof()) { 
      cout << "\nФайл Пуст!! Кодировать нечего."; 
      return 0;
   } 
   if (strEnd == "1"){ 
      outFile = "codedH_"; outFile += fileName;
    
      long long start_tik = clock();
      auto start = chrono::high_resolution_clock::now();
    
      root = haffmanCoder(file, outFile.c_str(), countStep, countSymbol);
      long long end_tik = clock();
      auto end = chrono::high_resolution_clock::now();
      chrono::duration<float> duration = end - start;
      
      printCode(); 
      cout << "\n\x1b[1;32mРазмер входного файла\x1b[1;33m "<< fileName << "\x1b[1;32m: \x1b[0m";
      printSizefile(fileName.c_str());
      cout << "\n\x1b[1;32mРазмер закодированного файла\x1b[1;33m "<< outFile << "\x1b[1;32m: \x1b[0m";
      sizef = printSizefile(outFile.c_str());
      cout << "\n\x1b[1;32mКоличество выполненных операций:\x1b[0m " << countStep; //cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep;
      cout << "\n\x1b[1;35mВремя выполнения кодирования:\x1b[0m " << duration.count() << " sec.";
      cout << "\n\x1b[1;35mВремя выполнения в тактах:\x1b[0m " << end_tik - start_tik << " тактов.";
      cout << "\n\x1b[1;35mДлина закодированной последовательности\x1b[0m L = " << countSymbol;
}


else{
 
    outFile = "codedFSh_"; outFile += fileName;
    long long start_tik = clock();
    auto start = chrono::high_resolution_clock::now();
    
    root = FanoSh(file, outFile.c_str(), countStep, countSymbol);
    long long end_tik = clock();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    //добавить отношение размеров для сравнения
   // cout << "\n\x1b[1;32mКоды символов для текста\x1b[1;33m " << fileName <<": \x1b[0m\n";
    printCode(); 
    cout << "\n\x1b[1;32mРазмер входного файла\x1b[1;33m  "<< fileName << "\x1b[1;32m: \x1b[0m";
    printSizefile(fileName.c_str());
    cout << "\n\x1b[1;32mРазмер закодированного файла\x1b[1;33m  "<< outFile << "\x1b[1;32m: \x1b[0m";
    sizef = printSizefile(outFile.c_str());
    cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m  " << stepF_Sh + stepMid; //cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep;
    cout << "\n\x1b[1;35mВремя выполнения кодирования(Шеннона): \x1b[0m  " << duration.count() << " sec.";
    cout << "\n\x1b[1;35mВремя выполнения кодирования в тактах: \x1b[0m  " << end_tik - start_tik << " тактов.";
    cout << "\n\x1b[1;35mДлина закодированной последовательности L = \x1b[0m  " << countSymbol;
}
    
    countStep = 0;
    if (countSymbol < 150) flag = 1;
    string outFile1 = "decod_"; outFile1 += fileName;
    string fileName1 = outFile;
    if (sizef < 1){
    	cout << "\n"; //printCode();
    	cout << "\nФайл слишком маленький для кодирования/декодирования";
    	return 0;
    }
    if (flag) cout << "\n\nЗакодированная последовательность: ";
    long long start_tik = clock();
    auto start = chrono::high_resolution_clock::now();
    file.open(fileName1.c_str(),ios::in | ios::binary);
    countStep = 0;
    decoder(file, outFile1.c_str(), countStep, countSymbol, root);
    long long end_tik = clock();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << "\n\x1b[1;32mРазмер исходного файла\x1b[1;33m "<< fileName1 << "\x1b[1;32m :\x1b[0m";
    printSizefile(fileName1.c_str());
    cout << "\n\x1b[1;32mКоличество выполненных операций:\x1b[0m " << countStep; //cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep;
    cout << "\n\x1b[1;32mВремя выполнения декодирования: \x1b[0m " << duration.count() << " sec.";
    cout << "\n\x1b[1;32mВремя выполнения в тактах: \x1b[0m " << end_tik - start_tik << " тактов.";

    countSymbol = 0;
    cout << "\n" << "Вы хотите продолжить \033[1;34m[y/n]\033[0m ? : ";
    cin >> strEnd;
    toLower(strEnd);
    while (strEnd!=stop && strEnd!=again){
        cout << "\n\033[1;31mОшибка, введите [y/n] :\033[0m";
        cin >> strEnd; toLower(strEnd);
    } 
   map<char,vector<bool> >::iterator il;
   for (auto it = table.begin(); it != table.end(); ++it)
   {
     table.erase(it->first);
   }
   // code.clear();
   
 }while(strEnd != "n");
	return 0;
}
