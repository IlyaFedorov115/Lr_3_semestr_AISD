#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <chrono>
#include <algorithm>  // sort
//#include <sys/stat.h>


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



Node* haffmanCoder(ifstream &f, const char* output, int &countStep, int &countSymbol){
    map<char,int> period; map<char,int>::iterator i;              //считываем из файла и заносим частоту 
    int k = 0;
    cout << "\n\x1b[1;32mЧастоты встречаемости символов: \x1b[0m\n";
    while (!f.eof()){                
	   char c = f.get();            
	    if (c == EOF)
	      continue;
	    period[c]++; countSymbol++;
	}
	//вывод полученных частот встречаемости  если че, то создать глобальный
    for (i = period.begin(); i != period.end(); ++i, k++){
        if (k == 3) { k = 0; cout << "\n"; }
        cout <<"\'"<< i->first << "\'" <<" -- "<< i->second<< "\t";
    }
    cout << "\n\n";   
    
    list<Node*> lst;              // список частот для сортировки в алгоритме
    map<char,int>::iterator j;
    for (j = period.begin(); j != period.end(); ++j){               //создаем список символов с их частотой
        Node *p = new Node;                                        //для сортировки 
        p->c = j->first;
        p->a = j->second;
        lst.push_back(p);                                             //добавить в конец
    }
    /// Node* makeTree(list<Node*> &lst){
    //////  создаем дерево
    
    if (lst.size() == 0) { cout<< "\n\x1b[1;31mError!! Элементов нет."; exit(1);} 
    if (lst.size() == 1) {
       Node *sonL = lst.front(); lst.pop_front();
       Node *parent = new Node(sonL, NULL); lst.push_back(parent);
    }
    while (lst.size() != 1){
        
      lst.sort(MyCompare());
    
      Node *SonL = lst.front();
      lst.pop_front();
      Node *SonR = lst.front(); 
      lst.pop_front();
     
      Node *parent = new Node(SonL,SonR); 
      lst.push_back(parent);  countStep++;
     }
     Node* root = lst.front();                  //можно вывести
     
     ////// создаем пары 'символ-код':			
   	 BuildTable(root);                        //можно вывести коды
   	 
     f.clear(); f.seekg(0);                   // перемещаем указатель снова в начало файла
    
     ofstream g(output, ios::out | ios::binary);	
     int count = 0; char buf = 0;
     while (!f.eof()){ 
      unsigned char c = f.get();  //if(c == EOF) continue;
	   vector<bool> x = table[c];
	   for(int n = 0; n < x.size(); n++){
	     buf = buf | x[n] << (7-count);   
	     count++;   
	     if (count == 8) { count = 0;   g << buf; buf = 0; } 
          }
     }
     
    f.close();  g.close(); 
    return root;
}



void decoder(ifstream &F, const char* outFile, int &countStep, Node* root = NULL){
   if (root == NULL){
      readBytefile(F);
      root = maketreeCode();
     // printCode();
   }
    Node *p = root;
	int count = 0; char byte; 
	byte = F.get();
	ofstream g(outFile, ios::out | ios::binary);
	while(!F.eof()){ 
	    countStep++;
	    bool b = byte & (1 << (7-count) ); 
		if (b){
		   p = p->right; 
	//	   if (p == NULL) { cout<<"\n\x1b[1;31mОшибка! Неверное кодирование!"; exit(1);}
		}
		else{
		   p = p->left;
//		   if (p == NULL) { cout<<"\n\x1b[1;31mОшибка! Неверное кодирование!"; exit(1);}
		}
	//	if (p->left == NULL && p->right == NULL && p->c) { 
	   if (p->left == NULL && p->right == NULL) {
		     g << p->c; 
		     p = root; 
		}  
/*		else {
		    cout<<"\n\x1b[1;31mОшибка! Неверное кодирование!"; exit(1);
		} */
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
	    period[c]++; countSymbol++;
	}
	
    vector<Node*> wperiod;
    map<char,int>::iterator j;
    for (j = period.begin(); j != period.end(); ++j){               //создаем список символов с их частотой
        Node *p = new Node;                                        //для сортировки 
        p->c = j->first;
        p->a = j->second;
        wperiod.push_back(p);                                             //добавить в конец
    }


    sort(wperiod.begin(), wperiod.end(), MyCompare());
    //вообще уже есть в countSymbol
    int S = 0; int E = 0; 
    vector<bool> Code;
    for(int i = 0; i != wperiod.size(); ++i){
        S += wperiod[i]->a;
        E++;
    }
    Node* root = F_Sh(wperiod, S, 0, E-1, Code);
      
    BuildTable(root);                        //можно вывести коды
   	 
     f.clear(); f.seekg(0);                   // перемещаем указатель снова в начало файла
    
     ofstream g(output, ios::out | ios::binary);	
     int count = 0; char buf = 0;
     while (!f.eof()){ 
      unsigned char c = f.get();  //if(c == EOF) continue;
	   vector<bool> x = table[c];
	   for(int n = 0; n < x.size(); n++){
	     buf = buf | x[n] << (7-count);   
	     count++;   
	     if (count == 8) { count = 0;   g << buf; buf = 0; } 
          }
     }
     
    f.close();  g.close(); 
    return root;

}


///////////////////////////////////////////////////////////////
int main (){
    
  string strEnd;    
  int countStep = 0;
  int countSymbol = 0;
  long sizeFile = 0;
  Node* root;     
do{
    
     printDialog();
     cin >> strEnd;
     while (strEnd != "1" && strEnd != "2"){
        cout << "\n\033[1;31mОшибка, введите [1/2/3]: \033[0m";
        cin >> strEnd; 
     } 
    
/////// Часть про кодирование и декодирование Хаффмана
     string fileName;  
     cout << "\x1b[1;32m\nВведите имя файла:\x1b[0m ";
     cin >> fileName;
     
     ifstream file(fileName.c_str(),ios::in | ios::binary);
     while(!file) {
        cout <<"\033[1;31m\nНе удается открыть файл.Введите корректное имя: \033[0m";
        cin >> fileName;
        file.open(fileName.c_str(),ios::in | ios::binary);
     }   
  string outFile; 
   
  if (strEnd == "1"){ 
    outFile = "codedH_"; outFile += fileName;
    
    auto start = chrono::high_resolution_clock::now();
    
    root = haffmanCoder(file, outFile.c_str(), countStep, countSymbol);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    
    //добавить отношение размеров для сравнения
    cout << "\n\x1b[1;32mКоды символов для текста\x1b[4;33m " << fileName <<" : \x1b[0m\n";
    printCode(); cout << "\n\x1b[1;32mРазмер входного файла\x1b[4;33m "<< fileName << "\x1b[1;32m :\x1b[0m";
    printSizefile(fileName.c_str());
    cout << "\n\x1b[1;32mРазмер закодированного файла\x1b[4;33m"<< outFile << "\x1b[1;32m:\x1b[0m";
    printSizefile(outFile.c_str());
    cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep; //cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep;
    cout << "\n\x1b[4;35mВремя выполнения кодирования: \x1b[0m" << duration.count() << " sec.";
   
    
}

/////////////////////////////////////////////////////////
/*
    string outFile1 = "decoded_"; outFile1 += fileName;
    string fileName1 = outFile;
    start = chrono::high_resolution_clock::now();
    file.open(fileName1.c_str(),ios::in | ios::binary);
    countStep = 0;
    decoder(file, outFile1.c_str(), countStep, root);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "\n\x1b[1;32mРазмер исходного файла\x1b[4;33m "<< fileName1 << "\x1b[1;32m :\x1b[0m";
    printSizefile(fileName1.c_str());
    cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep; //cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep;
    cout << "\n\x1b[4;35mВремя выполнения декодирования: \x1b[0m" << duration.count() << " sec.";
} 
*/
else{
 
    outFile = "codedFSh_"; outFile += fileName;
    auto start = chrono::high_resolution_clock::now();
    
    root = FanoSh(file, outFile.c_str(), countStep, countSymbol);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    //добавить отношение размеров для сравнения
    cout << "\n\x1b[1;32mКоды символов для текста\x1b[4;33m " << fileName <<" : \x1b[0m\n";
    printCode(); cout << "\n\x1b[1;32mРазмер входного файла\x1b[4;33m "<< fileName << "\x1b[1;32m :\x1b[0m";
    printSizefile(fileName.c_str());
    cout << "\n\x1b[1;32mРазмер закодированного файла\x1b[4;33m"<< outFile << "\x1b[1;32m:\x1b[0m";
    printSizefile(outFile.c_str());
    cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep; //cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep;
    cout << "\n\x1b[4;35mВремя выполнения кодирования(Шеннона): \x1b[0m" << duration.count() << " sec.";
}




    string outFile1 = "decoded_"; outFile1 += fileName;
    string fileName1 = outFile;
    auto start = chrono::high_resolution_clock::now();
    file.open(fileName1.c_str(),ios::in | ios::binary);
    countStep = 0;
    decoder(file, outFile1.c_str(), countStep, root);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << "\n\x1b[1;32mРазмер исходного файла\x1b[4;33m "<< fileName1 << "\x1b[1;32m :\x1b[0m";
    printSizefile(fileName1.c_str());
    cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep; //cout << "\n\x1b[1;32mКоличество выполненных операций: \x1b[0m" << countStep;
    cout << "\n\x1b[4;35mВремя выполнения декодирования: \x1b[0m" << duration.count() << " sec.";

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
   map<char,vector<bool> >::iterator il;
   for (auto it = table.begin(); it != table.end(); ++it)
   {
     table.erase(it->first);
   }
   // code.clear();
   
 }while(strEnd != "n");
	return 0;
}
