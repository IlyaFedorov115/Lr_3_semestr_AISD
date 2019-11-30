#ifndef PRINT_H
#define PRINT_H


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
    int k = 0;
    cout << "\n\x1b[1;32mКоды символов для данного текста: \x1b[0m\n";
    map<char,vector<bool> >::iterator ii;
    for (ii = table.begin(); ii != table.end(); ++ii, k++){
        if (k == 3) { k = 0; cout << "\n";}
        char c = ii->first;
        if (c == '\n')  cout <<"\'" <<"\\n" <<"\'" << " - ";
        else 
            cout <<"\'" <<c <<"\'" << " - ";
        vector<bool> x = table[c];
        for (int i = 0; i < x.size(); i++)
            cout << x[i];
        cout << "\t";    
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
    cout << "\n\x1b[1;33m\'1\'\x1b[0m -- Прочитать файл с сообщением, закодировать его\n\tи раскодировать это же сообщение.\n";
    cout << "\x1b[1;33m\'2\'\x1b[0m -- Прочитать файл с \x1b[4mзакодированным\x1b[0m сообщением и раскодировать его\n\t(в начале файла указаны коды символов).\n";
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







#endif
