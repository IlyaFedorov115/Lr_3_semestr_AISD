#include <iostream>
#include <cstring>
#include <fstream>
#define QUIT "quit"


using namespace std;


/* ПОСМОТРЕТЬ ЧТО ЧИСТИТЬ (МАССИВЫ И Т.Д) +++ ПРОБЛЕМЫ В ВЫВОДЕ ПРОМЕЖУТОЧНЫХ ДАННЫХ И АЛГОРИТМЕ */

class Vector {
 public:
    int* data;
    int size = 0;
    friend ostream &operator<<(ostream &stream, Vector obj);
};


ostream &operator<<(ostream &stream, Vector obj){
    int i = 0;
    for (i; i < obj.size-1 ; i++)
    {
        stream << obj.data[i] << ", ";
    }
    stream << obj.data[i] << "\n";
    return stream;
}


// НОВАЯ ВЕРСИЯ 

void readFile(const char *fileName, Vector &obj, int number){
    char ch; int count = 0;
    ifstream in(fileName, ios::in | ios::binary);
    if (!in){
        cout << "Не удается открыть файл.\n";
        return ;
    }
    
    while(in && number != 0)
      {
         in.get(ch);
         if(in && (ch <='9') && (ch >= '1'))
           {
               char buf[30];
               int i = 0;
               while((ch <='9') && (ch >= '1') && in)
                  {
                    buf[i++] = ch;
                    in.get(ch);
                   }
               obj.data[count++] = atoi(buf);
               number--;
           }
      }
      obj.size = count;
      cout << "Считанный из файла вектор: " << obj << "\n";
}


void transformVector(Vector &obj, int pos , int length,int depth){
    if(length > 2)
     {
        if(length % 2 == 1)
           {
            cout << obj << "\n";   
            transformVector(obj,pos,length/2+1, depth++);
            transformVector(obj,pos + length/2 +1,length/2, depth++);
           }
        else
           {
               cout << obj << "\n";
             transformVector(obj,pos,length/2,depth++);
             transformVector(obj,pos + length/2,length/2, depth++);
           }
    }

    if(length == 2 && (obj.data[pos+1] < obj.data[pos]))
      {
        int x = obj.data[pos];
        cout << obj << "\n";
        obj.data[pos] = obj.data[pos+1];
        obj.data[pos+1] = x;
       }

    if(length == 1) return;
    
     cout <<"глубина"<< depth << obj << "\n";
}


int isDigit(char* str){
    for (int i = 0; i < strlen(str) ; i++){
        if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
}


int isDigit(string str){
    for (int i = 0; i < str.length() ; i++)
        if (isdigit(str[i]) == 0) return 0;
    return 1;    
}


void toLower(string &str){
    int i = 0;
    while (str[i]){
        str[i] = tolower(str[i]);
        i++;
    }
}


void readConsole(Vector &obj){
  string str;
  cout << "Введите координаты вектора: \n";
  for (int i = 0; i < obj.size ;i++)
    {
       cout << i+1 << "-e число: ";
       cin >> str;
       while (!isDigit(&str[0])) // можно и стринг
         {
            cout << "Ошибка ввода. Попробуйте еще раз ввести число: ";
            cin >> str;
         }
       obj.data[i] = atoi(str.c_str());
    }
}


const string file = "file";
const string con = "con";

int main() // на всякий случай
{
    Vector obj;
    string str;

    do{
        cout << "Введите длинну вектора: ";
        cin >> str;
        while (!isDigit(&str[0])){
            cout << "Ошибка ввода. Попробуйте еще раз ввести число: ";
            cin >> str;
        }
        obj.size = atoi(str.c_str()); // !!! Почитать, создает ли новую строку
        obj.data = new int[obj.size];
        cout << "Если вы хотите считывать из файл, то введите \'file\' , если с консоли, то введите \'con\': ";
        cin >> str; toLower(str);
        while (str != file && str!=con)
          {
            cout << "Ошибка ввода, попробуйте снова: " ;
            cin >> str;
          }
          if (str == file)
            {
              string fileName;  
              cout << "Введите имя файла: ";
              cin >> fileName;
              readFile(fileName.c_str(),obj,obj.size);
            }
          else {
            readConsole(obj);
             }  
        transformVector(obj, 0, obj.size, 1);
        cout << obj;
        cout << "\n" << "Введите \'next\' для продолжения или \'end\' для выхода: "; //любой символ
        
        cin >> str; 
        cout << "\n";
        toLower(str);
        
    }while(str != "end");
    
    return 0;
}
