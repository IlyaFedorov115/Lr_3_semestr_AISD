#ifndef READCODE_H
#define READCODE_H

void err(){
    cout << "\x1b[1;31mОшибка!! Неверное задание\x1b[0m";
    exit(1);
}

void readBytefile(ifstream& f){
    char ch, cl = '/';
    while ( !((ch == '\n' && cl == '\n') || (cl == '\n' && (ch == '1'|| ch == '0'))) ){
        ch = f.get();
        while (isspace(ch))
           ch = f.get();
        if (isalpha(ch)){
            cl = f.get();
            while (cl == ' ') cl = f.get();
            if (cl == '1' || cl == '0'){
                while (cl == '1' || cl == '0'){
                    code.push_back(cl-'0');
                    cl = f.get();
                }
                if (!isspace(cl))
                    err();
                table[ch] = code; code.clear();
            }
        else 
            err();
        }   /////////////////
    }
  //  ungetc(ch, (FILE*)f);
    f.unget();
}


Node* makeNode(map<char,vector<bool> >::iterator &ii,int k){
    Node* son = new Node;
    if (k < ii->second.size()-1){
        k++; 
        if (ii->second[k] == 0)
            son->left = makeNode(ii,k);
        else 
            son->right = makeNode(ii,k);
    }
    else
        son->c = ii->first;
    return son;
}


void makeNode_(map<char,vector<bool> >::iterator &ii, int k, Node* tmp){
    if (k < ii->second.size()-1){
        k++; 
       // if(tmp->c) {cout << "\x1b[1;31mОшибка!! Код не префиксный.\x1b[0m"; exit(1);}
       if(isalpha(tmp->c)) {cout << "\x1b[1;31mОшибка!! Код не префиксный.\x1b[0m"; exit(1);}
        if (ii->second[k] == 0){
            if (tmp->left)
                makeNode_(ii, k , tmp->left);
            else{
                Node* son = new Node;
                son = makeNode(ii,k);
                tmp->left = son;
            }
        }
        else {
            if (tmp->right)
                makeNode_(ii, k , tmp->right);
            else{
                Node* son = new Node;
                son = makeNode(ii,k);
                tmp->right = son;
            }
         }
    }
    else{
        if (tmp->c)
        {cout <<"\033[1;31m\nОшибка! Неверные коды\033[0m"; exit(1); }
    }
}


Node* maketreeCode(){
    map<char,vector<bool> >::iterator ii;
    Node *root = new Node; int k = 0;
    if (table.empty()){
        cout << "\033[1;31m\nНет кодов!!\033[0m";
        exit(1);
    }
 /*   else if (table.size() == 1){
        ii = table.begin();
        Node* son = new Node; son->c = ii->first;
        if (ii->second[0] == 0)
            root->left = son;
        else
            root->right = son;
    } */
    else {
        for (ii = table.begin(); ii != table.end(); ++ii){    
            if (ii->second[k] == 0)
              {
               if (root->left == NULL)
                  root->left = makeNode(ii,k); 
               else
                  makeNode_(ii,k,root->left);
              }
            else
              {
               if (root->right == NULL)
                  root->right = makeNode(ii,k); 
               else
                  makeNode_(ii,k,root->right);  
              }
    
        }
    }
    return root;
}



////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ РАЗЛИЧНЫХ ЗАДАЧ

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



void pushVector(vector<char> &a, vector<char> &b){
    for (int i = 0; i < b.size(); i++)
        a.push_back(b[i]);
}




#endif


