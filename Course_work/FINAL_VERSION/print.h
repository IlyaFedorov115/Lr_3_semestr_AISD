#ifndef PRINT_H
#define PRINT_H
#include <sys/stat.h>

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



void printCode(){
    int k = 0; int i = 0; int len = 0;
    map<char,vector<bool> >::iterator ii;
    for (ii = table.begin(); ii != table.end(); ++ii, k++){
        if (k == 2) { k = 0; cout << "\n";}
        char c = ii->first;
        if (c == '\n')  cout <<"\'" <<"\\n" <<"\'" << " - ";
        else if (c == '\t') cout <<"\'" <<"\\t" <<"\'" << " - ";
        //else if (c == EOF) cout <<"\'" <<"EOF" <<"\'" << " - ";
        else if (int(c) < 0 || c == EOF) continue;
       // else if (int(c) < 0) cout <<"\'" <<"unknown" <<"\'" << " - ";
        else 
            cout <<"\'" <<c <<"\'" << " - ";
        vector<bool> x = table[c];
        for (i = 0; i < x.size(); i++){
            cout << x[i]; len++;
        }
       if (len > 8 && len < 12) { cout << "\t\t\t"; len = 0; }
       else if (len > 12) { cout << "\t"; len = 0;}
       else    { cout << "\t\t\t\t"; len = 0; }
      
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




void printDialog(){
    cout << "\n\x1b[1;32mВыберите способ работы:\x1b[0m";
    cout << "\n\x1b[1;33m\'1\'\x1b[0m -- Использовать алгоритм Хаффмана.\n";
    cout << "\x1b[1;33m\'2\'\x1b[0m -- Использовать алгоритм Фано-Шеннона.\n";
    cout << "выбор: ";
}


void printDialog1(){
    cout << "\n\x1b[1;32mВыберите:\x1b[0m";
    cout << "\n\x1b[1;33m\'1\'\x1b[0m -- Открыть файл.\n";
    cout << "\x1b[1;33m\'2\'\x1b[0m -- Создать случайный текст.\n";
    cout << "выбор: ";
}



void printTree(Node* root, int k = 2){          // вывод дерева 
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
    else {
        cout << "\nДерево пусто";
    }
}


int treeSize(Node* root){
    int l, r;
    if (root){
      if (root->left) l = treeSize(root->left); 
      if (root->left) r = treeSize(root->right);
      return l+r;
  }
  return 0;
}


int printSizefile(const char* fileName){
    struct stat st; 
    stat(fileName, &st);
    long sizeFile = st.st_size;
    if (sizeFile > 1024){ printf("%.1f Кб", float(sizeFile)/1024); cout << " ("<<sizeFile<<" б)";  return 2;}
    else {
        cout << sizeFile << " байт";
        return sizeFile;
    }
}


int sizeF(const char* fileName){
    struct stat st; 
    stat(fileName, &st);
    long sizeFile = st.st_size;
    return sizeFile;
}


void randomText(int len, const char* name, int end = 0) {
    if (end > 70) end = 70;
    if (end < 0) end = 2;
  //  fout.open("randomText.txt");
    ofstream fout(name, ios::out | ios::binary);    
   // len;
    static const char alphanum[] =
              "abcdef ghijk lmno pqrs tuvwxyz "
              "0123 456 789"
              "\n"
              ".,?! "
              "ABC DEF GHIJ KLMNOP QRST UVWXYZ ";
    //cout << sizeof(alphanum);              
    srand(time(0));
    for (int i = 0; i < len; i++) {
       if (end == 0)    
           fout << alphanum[rand() % (sizeof(alphanum) - 1)];
       else 
           fout << alphanum[rand() % (end)]; 
    }
    fout.close();
} 



#endif
