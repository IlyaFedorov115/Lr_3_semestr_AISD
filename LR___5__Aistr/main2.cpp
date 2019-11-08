#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
using namespace std;

class Node{
   public:
	 int a;
	 char c;
	 Node *left; 
	 Node* right;
	 Node(){
	     left = NULL;
	     right = NULL;
	 }

	 Node(Node *L, Node *R) { 
	    left =  L;
	    right = R;
	    a = L->a + R->a;  }
};


struct MyCompare
{
    bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
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


void decoder(ifstream &F){
      while(!F.eof()){ 
        char ch = F.get;
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



///////////////////////////////////////////////////////////////
int main (int argc, char *argv[]){
    
   //Версия для строки ################################################    
   
    string s = "Lolf dfdf dfs!!dfsf!!";
    map<char,int> m;                                    //словарь
    for (int i = 0; i < s.length(); i++){              //запоминаем число вхождений
        char c = s[i];
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
        t.sort(MyCompare);                     //каждый раз пересортируем список
        Node* sonL = t.front();
        t.pop_front();
        Node* sonR = t.front();
        t.pop_front();
        
        Node* parent = new Node(sonL, sonR);
        t.push_back(parent);
    }
    
    Node* root = t.front();                    //получаем корень
    
    BuildTable(root);                         //заполняем table кодами хаффмана для символов
    
    //вывод кода хаффмана 00011101110001010010101
    for (int i = 0; i < s.length(); i++){
        char c = s[i];
        vector<bool> x = table[c];
        
        for (int n = 0; n < x.size(); n++)
            cout << x[n];
    }
    
    // В Итоге мы закодировали сообщение
    
//Версия для строки ################################################      
////// считаем частоты символов	
	ifstream f("1.txt", ios::out | ios::binary);
	
	map<char,int> m;
	
	while (!f.eof()){           //считываем из файла и заносим частоту 
	   char c = f.get(); 
	   m[c]++;
	}

  
////// записываем начальные узлы в список list
	     	     
   list<Node*> t;
   map<char,int>::iterator itr;
   for(itr = m.begin(); itr != m.end(); ++itr){    // создаем список элемента с  
      Node *p = new Node;                          // их частотой
      p->c = itr->first;
      p->a = itr->second;  
      t.push_back(p);      
   }	
	

//////  создаем дерево		

  while (t.size()!=1){  
     t.sort(MyCompare());
    
     Node *SonL = t.front();
     t.pop_front();
     Node *SonR = t.front(); 
     t.pop_front();
     
     Node *parent = new Node(SonL,SonR); 
     t.push_back(parent);

  }
	//Node* root = makeTree(t);
	
	Node *root = t.front();   //root - указатель на вершину дерева

////// создаем пары 'символ-код':			

   	BuildTable(root);   
		
////// Выводим коды в файл output.txt

    f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла
    
	ofstream g("output.txt", ios::out | ios::binary);
    	
    int count=0; char buf=0;
    while (!f.eof()){ 
      char c = f.get();                //считываем символ
	  vector<bool> x = table[c];
	  for(int n = 0; n < x.size(); n++){
	    buf = buf | x[n]<<(7-count);      // записывает БАЙТАМИ в файл   
	    count++;   
	    if (count == 8) { count = 0; g << buf; buf = 0; } 
       }
    }

    f.close();
	g.close(); 
	
///// считывание из файла output.txt и преобразование обратно

	ifstream F("output.txt", ios::in | ios::binary);

	//setlocale(LC_ALL,"Russian"); // чтоб русские символы отображались в командной строке
	
	Node *p = root;
	count = 0; char byte; 
	byte = F.get();
	while(!F.eof()){   
	    bool b = byte & (1 << (7-count) );             //проверяем байты 
		if (b) 
		    p = p->right; 
		else 
		    p = p->left;
		if (p->left == NULL && p->right == NULL) {
		    cout << p->c; 
		    p = root;
		}
		count++;
		if (count == 8) {
		    count = 0; 
		    byte = F.get();
		}
	} ////
	
	F.close();	

	return 0;
}
