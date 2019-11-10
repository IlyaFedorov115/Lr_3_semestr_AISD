#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
using namespace std;

class Node{                           //класс узла дерева
   public:
	 int a;
	 char c;
	 Node *left;                       //левое и правое
	 Node* right;                      //поддеревья
	 Node(){
	     left = NULL;
	     right = NULL;
	 }

	 Node(Node *L, Node *R) { 
	    left =  L;
	    right = R;
	    a = L->a + R->a; 
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
    if (root->left==NULL && root->right==NULL) 
         table[root->c] = code;     
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


void decoder(ifstream &F, Node* root){
	 Node *p = root;
      while(!F.eof()){ 
        char ch = F.get();
        if (ch == '1')
		    p = p->right; 
		else if (ch == '0') 
		    p = p->left;
		else if (ch == ' ')
	       continue;
	    else
	       cout << "\nОшибка!! Неправильное кодирование сообщения!";
		if (p->left == NULL && p->right == NULL) {
		    cout << p->c; 
		    p = root;
		}
	    if (((p->left == NULL || p->right == NULL) && !(p->c)) || ((p->left == NULL || p->right == NULL) && (p->c))) 
	        cout << "Неверный вид кодирования!!";
	} ////

}



void printCode(){
    map<char,vector<bool> >::iterator ii;
    for (ii = table.begin(); ii != table.end(); ++ii){
        char c = ii->first;
        cout << "\n" << c << " - ";
        vector<bool> x = table[c];
        for (int i = 0; i < x.size(); i++)
            cout << x[i];
        //cout <<""<< ii->first << "" <<" -- "<< ii->second<< endl;
    }
}




void printCrypt(ifstream& f){
    f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла
	ofstream outF("output.txt", ios::out | ios::binary);
    
    outF <<"\nЗакодированное сообщение: ";
    cout << "\nЗакодированное сообщение: ";	
    int count = 0; char buf = 0;
    while (!f.eof()){ 
      char c = f.get();                //считываем символ
	  vector<bool> x = table[c];
	  for(int i = 0; i < x.size(); i++){
	    cout << x[i];
	    outF << x[i];
	  }
    }

}



///////////////////////////////////////////////////////////////
int main (int argc, char *argv[]){
    
    
    string fileName;  
    cout << "\033[0;32mВведите имя файла:\033[0m ";
    cin >> fileName;
    ifstream f(fileName.c_str(),ios::in | ios::binary);
    while(!f) {
        cout <<"\033[1;31mНе удается открыть файл.Введите корректное имя: \033[0m";
        cin >> fileName;
        f.open(fileName.c_str(),ios::in | ios::binary);
    }
    
	map<char,int> m;
	while (!f.eof()){           //считываем из файла и заносим частоту 
	   char c = f.get(); //  getc getch
	   if (c == EOF)
	    continue;
	   cout << " " << c;
	   m[c]++;
	}

    map<char,int>::iterator i;                  //вывод полученных частот встречаемости 
    for (i = m.begin(); i != m.end(); ++i){
        cout <<"\'"<< i->first << "\'" <<" -- "<< i->second<< endl;
    }
    
    
    list<Node*> t;
    for (i = m.begin(); i != m.end(); ++i){           //создаем список символов с их частотой
        Node *p = new Node;                           //для сортировки 
        p->c = i->first;
        p->a = i->second;
        t.push_back(p);                    //добавить в конец
    }
    
    
    while (t.size() != 1){                    //создаем дерево Хаффмана
        t.sort(MyCompare());                     //каждый раз пересортируем список
        Node* sonL = t.front();
        t.pop_front();
        Node* sonR = t.front();
        t.pop_front();
        
        Node* parent = new Node(sonL, sonR);
        t.push_back(parent);
    }
    
    //Node* root = makeTree(t);
    Node* root = t.front();                    //получаем корень
    
    BuildTable(root);                         //заполняем table кодами хаффмана для символов
    
    
    map<char,vector<bool> >::iterator ii;
    for (ii = table.begin(); ii != table.end(); ++ii){
        char c = ii->first;
        cout << "\n" << c << " - ";
        vector<bool> x = table[c];
        for (int i = 0; i < x.size(); i++)
            cout << x[i];
        //cout <<""<< ii->first << "" <<" -- "<< ii->second<< endl;
    }

 // printCode(); можно заменить т.к. глобальный вект
		
////// Выводим коды в файл output.txt

    f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла
    
    //printCrypt(f);     Без clear и seekg

	ofstream outF("output.txt", ios::out | ios::binary);

    f.close();
	outF.close(); 
	
	
	
///// считывание из файла output.txt и преобразование обратно


	ifstream F("output.txt", ios::in | ios::binary);

	decoder(F,root);
	
	F.close();	

	return 0;
}
