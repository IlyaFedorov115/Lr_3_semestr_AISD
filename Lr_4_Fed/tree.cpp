/******************************************************************************
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <iostream>

using namespace std;
template <typename base>
struct node {
	base data;
	node<base> *left;
	node<base> *right;
	node () { left = NULL; right = NULL;}
};
	
typedef node<base> *binTree; // "представитель" бинарного дерева


	base RootBT (binTree); // для непустого бин.дерева
	binTree Left (binTree);// для непустого бин.дерева
	binTree Right (binTree);// для непустого бин.дерева
	binTree ConsBT(const base &x, binTree &lst,  binTree &rst);
	void destroy (binTree&);


//-------------------------------------
base RootBT(binTree obj){			// для непустого бин.дерева	
  if (obj == NULL) {
	  cerr << "Error: RootBT(null) \n"; 
	  exit(1); 
   }
  else return obj->data;
}
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
binTree ConsBT(const base &x, binTree &lst,  binTree &rst){	
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



void passWidth(binTree b){
    
}



int main()
{
    cout<<"Hello World\n";

    return 0;
}
