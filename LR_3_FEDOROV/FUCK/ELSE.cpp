#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define SIZE 500
string file = "f";
string con = "c";
string stop = "n";
string again = "y";

int step = 1;


class stack{
  public:
    int array[SIZE];
    int topElem;
  //  int size;
  public:
    stack();
    //stack(const stack &ob);
    //~stack();
    bool isEmpty();
    int push(int a);
    void pop();
    int top();
    int pop2();
    bool isOne();
 
};

/*
stack::stack(int maxsize = SIZE){
    array = new int [maxsize];
    int size = maxsize;
    int topElem = -1;
} */

stack::stack(){
    //array = new int [SIZE];
   // int size = 0;
    topElem = -1;
}

/*
stack::stack(const stack &ob){
    int size = ob.size;
    int topElem = ob.topElem;
    array = new int [size];
    for (int i = 0; i < size; i++){
        array[i] = ob.array[i];
    }
   
}
*/
/*
stack::~stack(){
    delete [] array;
} */ 

bool stack::isEmpty(){
    return topElem == -1;
}


int stack::push(int a){
    if (topElem == SIZE-1){
        cout << "Стэк заполнен!"; exit(1);
        return 0;
    }
    topElem++;
   // size++;
    array[topElem] = a;
    return 1;
}

void stack::pop(){
    if (topElem == -1){
        cout << "Стэк пуст!"; exit(1);
        //return NULL;
    }
    topElem--;
   // size--;
}

int stack::top(){
    if (topElem == -1){
        cout << "Стэк пуст"; exit(1);
        //return;
    }
    return array[topElem];
}

int stack::pop2(){
    if (topElem == -1){
        cout << "Стэк пуст"; exit(1);
    }
    int a = top();
    pop();
    return a;
}

bool stack::isOne(){
    if (topElem == 0)
        return true;
    else 
        return false;
}


int isDigit(char* str){
    if (((str[0] == '-' || str[0] == '+') && strlen(str)>1) || isdigit(str[0])){
       for (int i = 1; i < strlen(str) ; i++){
            if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
    }
    else 
        return 0;
} 

/*
int postfixCalc(stack& obj,istream &stream){
    int a = 0;
    char buf[256];
    while (in.getline(buf, 256, ' ')) {
     if (isDigit(buf))
        cout << "\nПоложит число" << atoi(buf);
     if (strlen(buf) == 1 && buf[0] == '+')
        cout << "\nСуммировать";
     if (strlen(buf) == 1 && buf[0] == '-')    
        cout << "\nРазность";
     if (!isDigit(buf) && strlen(buf) > 1)
        cout << "\nВведен некорректный символ: "<< buf[0];
    }
}
*/

void toLower(string &str){
    int i = 0;
    while (str[i]){
        str[i] = tolower(str[i]);
        i++;
    }
}


void readFile(istream &stream, char* buf){
    stream.read(buf,sizeof(buf));
    cout << "\nСчитано из файла: ";
    for (int i = 0; i < strlen(buf); i++)
        cout << buf[i];
}


void readConsole(char* buf){
    cout << "\033[0;32mВведите выражение в постфиксной форме:\033[0m ";    
    char c = getchar(); int i = 0;
    while (c != '\n')
      {
        buf[i++] = c;
        c = getchar();
      }
}

void fixed(){
    cin.clear(); 
    while (cin.get() != '\n');
}



int main(){
    string str;
    stack obj;
do{ 
    char buf[256];
    int res = 0;
   // stack obj;
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
          readFile(in,buf);
       }
    else 
        {
          cout << "\033[0;32mВведите выражение в постфиксной форме:\033[0m ";
          fixed();
          //char c;
          //cin >> c;
          char c = getchar(); int i = -1;
         while (c != '\n')
             {
                 i++;
                 buf[i] = c;
                 
                // cin >> c;
                 c = getchar();
             } 
          //readLisp(cin,obj);
          //fixed();
        } 
    cout << "\n\n СТРОКА  "<<buf << "\n";
    cout << "\nдлина строки = " << strlen(buf) << endl;
    int i = 0;
    while(i < strlen(buf)) 
      {
        cout << "шаг " << step++ << " считаный символ " << buf[i] << endl;
        if (buf[i] == '+')
          {
            if (obj.isOne() || obj.isEmpty())
              {
                 cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
              }
            res = obj.pop2() + obj.pop2();
            obj.push(res);
          }
       else if (buf[i] == '*')
          {
            if (obj.isOne())
              {
                cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
              }
            res = obj.pop2() * obj.pop2();
            obj.push(res);              
          }
       else if (buf[i] == '-' && !(isdigit(buf[i+1])))
          {
              
            if (obj.isOne())
              {
                cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
              }
            int a = obj.pop2();
            res = obj.pop2() - a;
            obj.push(res);       
          } 
       else if (buf[i] == '^')
          {
            if (obj.isOne())
              {
                cout << "\nОшибка! В стэке не хватает чисел!"; exit(1);
              }
            int a = obj.pop2();
            res = pow(obj.pop2(), a);
            obj.push(res);
          }          
       else if ((buf[i] == '-') && (buf[i+1] >= '0') && (buf[i+1] <= '9'))
            { 
              obj.push(0);
              while ((buf[i] >= '0') && (buf[i] <= '9')) 
			  {
			    obj.push(10*obj.pop2() + (buf[i++]-'0'));
			  } 
			  obj.push(obj.pop2()*(-1));
              cout << "\nПоложили в стэк число:" << obj.top() << "\n";
            } 
       else if ((buf[i] >= '0') && (buf[i] <= '9') || (buf[i] == '+') && (buf[i+1] >= '0') && (buf[i+1] <= '9'))
            { 
              obj.push(0);
              while ((buf[i] >= '0') && (buf[i] <= '9')) 
			  {
			    obj.push(10*obj.pop2() + (buf[i++]-'0'));
			  } 
              cout << "\nПоложили в стэк число:" << obj.top() << "\n";
            }            
       else if (buf[i] == ' '){
            while (buf[i] == ' '){
                cout << "\nПРОБЕЛ";
                i++;
            }
        }
        else
            {
              cout << "\n\033[1;31mОшибка! Считан не корректный символ\033[0m "<< buf[i] <<"\n";
              exit(1);
            }     
      }
   if(!(obj.isOne()) || obj.isEmpty()){
       cout << "\n\033[1;31mОшибка! В стэке не одно число!\033[0m ";
       exit(1);
   } 
    cout << "\n" << "\033[0;32mРезультат:\033[0m " ;
    cout << obj.pop2();
    cout << "\n" << "Вы хотите продолжить \033[1;34m[y/n]\033[0m ? : ";
    cin >> str;
    toLower(str);
    while (str!=stop && str!=again){
        cout << "\nОшибка, введите [y/n] :";
         cin >> str; toLower(str);
    }
    cout << "\n"; step = 1;
    
}while(str != "n");    
    
    return 0;
}
