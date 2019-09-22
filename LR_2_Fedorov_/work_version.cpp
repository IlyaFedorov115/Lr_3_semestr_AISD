#include <iostream>

using namespace std;
struct s_expr;
void readConsole(s_expr*&);
void write_lisp (const s_expr* x);
void write_seq (const s_expr* x);
void read_s_expr(char , s_expr*& ); 
void read_seq (s_expr*& );
//struct s_expr; // структура узла списка

struct two_ptr{ // 
	s_expr *head;
	s_expr *tail;
};	

struct s_expr{
  bool tag; // true: atom, false: pair
  union  
	 {
	   char atom;
	   two_ptr pair;	
	  }node;		//end union node
};			 

	
typedef s_expr *lisp;

bool isAtom(const s_expr* obj){	
    if(obj == NULL) return false;
	else return (obj->tag);
}

bool isNull(const s_expr* obj){ 
    return (obj == NULL);
}


s_expr* retHead(const s_expr* obj){      // PreCondition: not null (obj)
	if (obj != NULL) 
	 {
	   if (!isAtom(obj)) return obj->node.pair.head;
	   else { cerr << "Error: Head(atom) \n";  exit(1); }
	 }
	else 
	 { 
	  cerr << "Error: Head(nil) \n"; exit(1);
	 }
}


s_expr* retTail(const s_expr* obj){   // PreCondition: not null (obj)
   if (obj != NULL)
     {
      if (!isAtom(obj))   return obj->node.pair.tail;
	  else { cerr << "Error: Tail(atom) \n"; exit(1); }
     }
   else 
	  { 
	    cerr << "Error: Tail(nil) \n";exit(1);
	  }
}




s_expr* cons(s_expr* hd, s_expr* tl){    // PreCondition: not isAtom (t)
   s_expr* obj;
   if (isAtom(tl)) 
     { cerr << "Error: Tail(nil) 45\n"; exit(1);}
   obj = new s_expr; 
   if ( obj == NULL)	
     {cerr << "Memory not enough\n"; exit(1); } 	// не выделена динамическая память
   obj->tag = false;
   obj->node.pair.head = hd;
   obj->node.pair.tail = tl;
   return obj;	
}



s_expr* makeAtom(char x){
    s_expr* obj;
	obj = new s_expr;
	obj->tag = true;
	obj->node.atom = x;
	return obj;
}


void destroy (s_expr* obj) {
   if (obj != NULL) 
     {
	  if (!isAtom(obj)) 
	     {
			destroy(retHead(obj));
			destroy(retTail(obj));
		 } 
	 delete obj;
	}
	else cout << "Obj is nil "; // obj == NULL
}

char getAtom(const s_expr* obj){
   if (!isAtom(obj)) 
    { 
     cerr << "Error: getAtom(obj) for !isAtom(obj) \n";
     exit(1);
    }
   else return (obj->node.atom);
}


// ввод списка с консоли
void readConsole(s_expr*& obj){
  char x;
  do 
    cin >> x;
  while (x == ' ');
  read_s_expr(x, obj);
} 

//...........................
void read_s_expr(char prev, s_expr*& obj){   //prev - ранее прочитанный символ}
  if (prev == ')') 
     {cerr << " ! List.Error 1 " << endl; /* exit(1); */ } 
  else if ( prev != '(' ) 
    {
     obj = makeAtom(prev);
    }  
  else 
     read_seq(obj);
} 

//...........................
void read_seq (s_expr*& obj){	
  char x; 
  s_expr* p1;
  s_expr* p2;
  if (!(cin >> x)) {cerr << " ! List.Error 2 " << endl; exit(1);}
  while  (x == ' ') 
	 cin >> x;
  if (x == ')') 
     obj = NULL;
  else {
	read_s_expr(x, p1);
	read_seq(p2);
	obj = cons(p1, p2);
	} 
} 

// ѕроцедура вывода списка с обрамл¤ющими его скобками - write_lisp,
//  а без обрамл¤ющих скобок - write_seq


void write_lisp (const s_expr* x){   //пустой список выводитс¤ как () 
	if (isNull(x)) 
	   cout << " ()";
	else if (isAtom(x)) 
	   cout << ' ' << x->node.atom;
	else { //непустой список} 
	   cout << " (" ;
	   write_seq(x);
	   cout << " )";
	}
} // end write_lisp

//...........................
void write_seq (const s_expr* x)  
{//выводит последовательность элементов списка без обрамл¤ющих его скобок
	if (!isNull(x)) {
		write_lisp(retHead(x)); 
		write_seq(retTail(x));
	}
}
//...........................
s_expr* copy(const s_expr* x)
{	if  (isNull(x)) 
        return NULL;
	else if (isAtom(x)) 
	    return makeAtom(x->node.atom);
	else 
	    return cons(copy(retHead(x)), copy(retTail(x)));
} //end copy-lisp














int main()
{
    cout<<"Hello World \n";
    s_expr* s1, s2, s3;
	cout << "введите list1:" << endl;
	readConsole (s1);
	cout << "введен list1: " << endl;
	write_lisp (s1);
	cout << endl;

    return 0;
}
