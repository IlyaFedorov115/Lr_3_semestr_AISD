#include <iostream>
#include <fstream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <queue>
#define Len 80

using namespace std;
string file = "f";
string con = "c";
string stop = "n";
string again = "y";


template <typename base>
struct node {
	base data;
	node<base> *left;
	node<base> *right;
	node () { left = NULL; right = NULL;}
	friend class Tree;
};
	
typedef node<char> *binTree; // "представитель" бинарного дерева

class Tree{
  public:
    binTree root;
    int width;
    int maxrow, offset; // максимальная глубина, смещение корня
    char** Screen;
    void OutTree();
    void clrscr();
    void OutNodes(binTree v, int r, int c); // выдача поддерева
    Tree(int maxrow, binTree rot);
    ~Tree();
};


//-------------------------------------	
binTree Left(binTree obj){		// для непустого бин.дерева
	if (obj == NULL) { 
	    cerr << "Error: Left(null) \n"; exit(1);    //переданный узел нулевой
	}
    else 
       return obj->left;
}
//-------------------------------------	
binTree Right(binTree obj){		// для непустого бин.дерева
	if (obj == NULL) { 
	    cerr << "Error: Right(null) \n";             //переданный узел нулевой
	    exit(1); 
	}
	else 
	    return obj->right;
}
//-------------------------------------		
template <typename base>
binTree ConsBT(base x, binTree &lst,  binTree &rst){	
	binTree p;
	p = new node<base>;
	if (p != NULL)	{ 	
		p->data = x;
		p->left = lst;
		p->right = rst;
		return p;
	}
	else {
	    cerr << "Memory not enough\n"; exit(1);
	}
}
//-------------------------------------			
void destroy (binTree &tmp){
	if (tmp != NULL)	{
		destroy (tmp->left);
		destroy (tmp->right);			
		delete tmp;
		tmp = NULL;
	}
}

bool isNull(binTree b){
    return (b == NULL);
}


void outputTree(binTree Ptr, int totalSpace)
        {
            while(Ptr != NULL)
            {
                outputTree(Ptr -> right, totalSpace + 5);
 
                for(int i = 1; i <= totalSpace; i++)
                    cout << " ";
 
                cout << Ptr -> data << "\n";
 
                Ptr = Ptr -> left;
                totalSpace += 5;
            }
}

///////////////////////////////
//Функции класса 



Tree::Tree(int depth, binTree rot){
    maxrow = depth;
    root = rot; width = 80;
    if (maxrow > 5)
        width = 120;
    offset = width/2;
    Screen = new char* [maxrow];
    for(int i = 0; i < maxrow; i++)
        Screen[i] = new char[width];
}

Tree::~Tree(){
    for(int i = 0; i < maxrow; i++)
    delete []Screen[i];
    delete []Screen;
    //delete root;
}





void Tree::OutTree(){
    clrscr();
    OutNodes(root, 1, offset);
    if (root == NULL){
        cout << "..........................Дерево пусто...........................";
        return;
    }
    for(int i = 0; i < maxrow; i++){
        Screen[i][width-1] = 0;
        cout << '\n' << Screen[i];
    }
    cout << '\n';
}



void Tree::clrscr(){
    for(int i = 0; i < maxrow; i++)
    memset(Screen[i], '.', width);
}

void Tree::OutNodes(binTree v, int r, int c){
    if (r && c && (c < width)) 
    Screen[r-1][c-1] = v->data; // вывод метки
    if (r < maxrow){
     if (v->left) OutNodes(v->left, r+1, c - (offset >> r));
        if (v->right) OutNodes(v->right, r+1, c + (offset >> r));
    }
}










//////////////////////////////
////////////////////////////
//////////////////////
/////////////

/// Алгоритм рабочий
void passWidth(binTree b){
    int n = 0; int i = -1;
    char res[80];
    queue <binTree> q;
    binTree p;
    q.push(b);
    cout << "\nНачало алгоритма обхода в ширину!";
    while(!q.empty()){
        p = q.front();
        cout << "\nЗанесли в очередь: " << p->data;
        q.pop(); res[++i] = p->data;
        n++;
        if (!isNull(Left(p)))
            q.push(Left(p));
        else
            cout << "\n     Левого сына нет.";
        if (!isNull(Right(p)))
            q.push(Right(p));
        else
            cout << "\n     Правого сына нет.";
     }  
    cout << "\nОбход в ширину:"; 
    for (int j = 0; j<= i; j++)
        cout << " " << res[j];
    cout << "\nПройдено узлов: "<< n << "\n";
}



binTree enterBT (istream& stream){	   
    char ch;
	binTree p, q;
	stream >> ch;
	if (ch=='/') 
	   return NULL;
	else {
	   p = enterBT(stream);
	   q = enterBT(stream); 
	   return ConsBT(ch, p, q);
	}
}


int hBT(binTree b)
	{
		if (isNull(b)) return 0;
		else return max (hBT (Left(b)), hBT(Right(b))) + 1;
	}

//////////////////////
/////////////////////
/////////////////////
//////////////////////
//////////////////////

void readSexpr(istream& stream,char prev, binTree&);
void readSeq(istream& stream,binTree&);

void readLisp(istream &stream, binTree& obj){
  char x;
  do 
    stream >> x;
  while (x == ' ');
  readSexpr(stream , x, obj);
} 


void readSexpr(istream &stream,char prev, binTree& obj){   //prev - ранее прочитанный символ
  if (prev == ')'){
      cerr << "\033[1;31mОшибка!\033[0m Символ \033[1;34m\')\'\033[0m встречен раньше \033[1;34m\'(\'\033[0m " << endl; exit(1);  } 
  else if (prev == '#')
      obj = NULL;
 /* else if (prev != '(') 
    {
     binTree p;
     p = new node<char>;
     p->data = prev;
     return p;
    } */ 
  else if (prev == '(')
    readSeq(stream, obj);
} 


void readSeq(istream &stream, binTree& obj){	
  char x; 
  binTree p1,p2;
  if (!(stream >> x)){
      cerr << "\033[1;31mОшибка!\033[0m Не найден конец списка." << endl; exit(1);
  }
  while(x == ' ') 
	 stream >> x;
  if (x == ')' || x == '#') 
     obj = NULL;
  else if (x == '(')
     readSeq(stream,obj);
  else{
   //  p->data = x; 
    // readLisp(stream, p1);
    // readLisp(stream, p2);
     readSeq(stream,p1);
     readSeq(stream,p2);
     obj = ConsBT(x, p1 , p2); 
	} 
} 



///////////////////////////////
//////////////////////////////
/////////////////////////////
///////////////////////////////
//////////////////////////////
/////////////////////////////



void fixed(){
    cin.clear(); 
    while (cin.get() != '\n');
}

void toLower(string &str){
    int i = 0;
    while (str[i]){
        str[i] = tolower(str[i]);
        i++;
    }
}


int main()
{

  
    //res = enterBT();
  /*  readLisp(cin, res);
    Tree tree(hBT(res),res);
    tree.OutTree();
 passWidth(res); */
 
 
 
 string str;

do{
    binTree res;
    cout << "Считать из файла - \033[1;34m\'f\' , \033[0m или с консоли - \033[1;34m\'c\': \033[0m";
    cin >> str; toLower(str);
    while (str!=file && str!=con)
      {
        cout << "\033[1;31mОшибка ввода, попробуйте снова: \033[0m" ;
        cin >> str;
     }
     
     if (str == file)
       {
         string fileName;  
         cout << "\033[0;32mВведите имя файла:\033[0m ";
         cin >> fileName;
         ifstream in(fileName.c_str(),ios::in | ios::binary);
         while(!in)
           {
             cout <<"\033[1;31mНе удается открыть файл.Введите корректное имя: \033[0m";
             cin >> fileName;
             in.open(fileName.c_str(),ios::in | ios::binary);
            }
          res = enterBT(in);
          in.close();
       }
     else {
      cout << "\033[0;32mВведите узлы БД в формате КЛП (пустой узел - \'/\') :\033[0m ";
      res = enterBT(cin);
     }
     
    Tree tree(hBT(res),res);
    cout << "\nСчитанное дерево:\n";
    tree.OutTree();
    passWidth(res);
    
    
    
    cout << "\n" << "Вы хотите продолжить \033[1;34m[y/n]\033[0m ? : ";
    cin >> str;
    toLower(str);
    while (str!=stop && str!=again){
        cout << "\n\033[1;31mОшибка, введите [y/n] :\033[0m";
        cin >> str; toLower(str);
    }
    
    destroy(res);    
 
}while (str != "n");    
    return 0;
}
