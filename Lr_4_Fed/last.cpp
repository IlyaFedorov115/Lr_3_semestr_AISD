/******************************************************************************
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include <queue>
#define Len 80

using namespace std;



template <typename base>
struct node {
	base data;
	node<base> *left;
	node<base> *right;
	node () { left = NULL; right = NULL;}
/*	bool isNull(node<char> *);
	base RootBT (node<char> *); // для непустого бин.дерева
	node<char> * Left (node<char> *);// для непустого бин.дерева
	node<char> * Right (node<char> *);// для непустого бин.дерева
	node<char> * ConsBT(const base &x, node<char> * &lst,  node<char> * &rst);
	void destroy (node<char> *&);
	
	*/
	
};
	
typedef node<char> *binTree; // "представитель" бинарного дерева




//-------------------------------------
/*
template <typename base>
base RootBT(){			// для непустого бин.дерева	
  if (obj == NULL) {
	  cerr << "Error: RootBT(null) \n"; 
	  exit(1); 
   }
  else return obj->data;
} */
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


/// Алгоритм рабочий
void passWidth(binTree b){
    //Queue buf;
    int n = 0;
    cout << "\nОбход в ширину: ";
    queue <binTree> q;
    binTree p;
    //buf.pushTail(b);
    q.push(b);
   // while(!Null(buf)){
    while(!q.empty()){
        //p = buf.popHead();  
        p = q.front();
        q.pop();
        n++;
        cout << p->data << " ";
        if (!isNull(Left(p)))
            //buf.pushTail(Left(p));
            q.push(Left(p));
        if (!isNull(Right(p)))
            q.push(Right(p));
           // buf.pushTail(Right(p));
     }    
    cout << "  Пройдено узлов: "<< n << "\n";
}


binTree enterBT (){	   
    char ch;
	binTree p, q;
	cin >> ch;
	if (ch=='/') 
	   return NULL;
	else {
	   p = enterBT();
	   q = enterBT(); 
	   return ConsBT(ch, p, q);
	}
}


//////////////////////
/////////////////////
/////////////////////
//////////////////////
//////////////////////

binTree readSexpr(istream& stream,char prev);
binTree readSeq(istream& stream);

binTree readLisp(istream &stream){
  char x;
  do 
    stream >> x;
  while (x == ' ');
  readSexpr(stream , x);
} 


binTree readSexpr(istream &stream,char prev){   //prev - ранее прочитанный символ
  if (prev == ')'){
      cerr << "\033[1;31mОшибка!\033[0m Символ \033[1;34m\')\'\033[0m встречен раньше \033[1;34m\'(\'\033[0m " << endl; exit(1);  } 
  else if (prev != '(') 
    {
     binTree p;
     p = new node<char>;
     p->data = prev;
     return p;
    }  
  else 
    return readSeq(stream);
} 


binTree readSeq(istream &stream){	
  char x; 
  binTree p1,p2,p3;
  if (!(stream >> x)){
      cerr << "\033[1;31mОшибка!\033[0m Не найден конец списка." << endl; exit(1);
  }
  while(x == ' ') 
	 stream >> x;
  if (x == ')') 
     return NULL;
  else if (x == '(')
     return readSeq(stream);
  else{
   //  p->data = x; 
     p1 = readSeq(stream);
     p2 = readSeq(stream);
     return ConsBT(x, p1 , p2); 
	} 
} 



///////////////////////////////
//////////////////////////////
/////////////////////////////
///////////////////////////////
//////////////////////////////
/////////////////////////////



int main()
{
    cout<<"Hello World\n";
    binTree res;
  //  res = enterBT();
  res = readLisp(cin);
   // displayBT(res,1);
//  print_Tree(res,0);
   outputTree(res,0);
 // printLevel(res,1);
// passWidth(res);
    return 0;
}
