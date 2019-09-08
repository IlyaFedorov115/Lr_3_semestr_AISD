#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


class Vector {
 public:
    int* data;
    int size;
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


/*
void split(char *buf, Vector &obj){
    char *tok = " ,";
    char *pch = strtok(buf, tok);//подстрока до первого разделителя
    for(int i = 0; pch && i < sizeof(obj.data)/sizeof(obj.data[0]); i++)
    {
        obj.data[i] = atoi(pch);
        pch = strtok(NULL,tok);
    }
} */


void split(char *buf, Vector &obj){
    int i = 0;
    char *tok = " ,";
    char *pch = strtok(buf, tok);//подстрока до первого разделителя
    while (pch != NULL)                         // пока есть лексемы
     {
      obj.data[i++] = atoi(pch);
      pch = strtok(NULL, " ,");
      obj.size++;
     }
} 


void put_from_file(const char *fileName, Vector &obj){
    char ch;
    char *buf; //dont know
    int count = 0;
    int i,j = 0;
    ifstream in(fileName, ios::in | ios::binary);
    if (!in){
        cout << "Не удается открыть файл.\n";
        return ;
    }
    while (in.get(ch))
       count++;  // если равно числу, то второй коунт
    buf = new char[count];   
    obj.data = new int[count];
    in.seekg(ios::beg); // или fstream стр 468
    
    in.read(buf, count);
    
    split(buf, obj);
    
  /*  while (in){
        in.get(ch);
        if(in && (ch <='9') && (ch >= '1')) buf[i++] = ch; // как сделать динамическую память
        else 
        {
            buf[i] = ch;
            obj.data[j++] = atoi(buf);    
        }
    }  */
}



/*
void put_data(Vector &vect, int* arr, int len){
    vect.data = new int[len];
    vect.size = len;
    for (int i = 0; i < len; i++){
        vect.data[i] = arr[i];
    }
  //  delete [] arr;
}
void print_vector(Vector &vect){
    cout << "Вектор: (";
    for (int i = 0; i < vect.size; i++){
        if (i != 0) cout << ",";
        cout << vect.data[i];
    }
    cout << ")";
}
*/


void change_vector(Vector &obj, int pos , int length){
    if(length > 2)
     {
        if(length % 2 == 1)
           {
            change_vector(obj,pos,length/2+1);
            change_vector(obj,pos + length/2 ,length/2);
           }
        else
           {
             change_vector(obj,pos,length/2);
             change_vector(obj,pos + length/2,length/2);
           }
    }

    if(length == 2 && (obj.data[pos+1] < obj.data[pos]))
      {
        int x = obj.data[pos];
        obj.data[pos] = obj.data[pos+1];
        obj.data[pos+1] = x;
       }

    if(length == 1) return;
    
    cout << obj << "\n";
}



int is_digit(char* str){
    for (int i = 0; i < strlen(str) ; i++){
        if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
}


int main(int argc, char* argv[]) // на всякий случай
{
    /*    char ch;
    if(argc!=2){
        cout << "Применение: имя_программы <имя_файла>\n";
        return 1;
    } */
    
    
    char exit_str[20];
    vect vector;

    do{
        string str;
        cout << "Введите длинну вектора: ";
        cin >> str;
       // const char* str2 = str.c_str();
        while (!is_digit(&str[0])){
            cout << "Ошибка ввода. Попробуйте еще раз ввести число: ";
            cin >> str;
        }
        obj.size = atoi(str.c_str()); // !!! Почитать, создает ли новую строку
        int arr[vector.size];
        vector.arr = arr;

        printf("Введите вектор \n");
        for (int i=0;i<vector.size;i++){
            printf("%d число:",i+1);
            fgets(str, sizeof(str), stdin);
            while (sscanf(str, "%d", &arr[i]) != 1) {
                printf("Ошибка ввода. Попробуйте ещё:");
                fgets(str, sizeof(str), stdin);
            }
        }

        change(vector,0,vector.size);
        print_vector(vector,0,vector.size);

        printf("Введите new для продолжения\n");
        scanf("%s",exit_str);
        printf("\n");
       fgets(str, sizeof(str), stdin);
    }while(strcmp(exit_str,"new") == 0);
    
    
    
  
    return 0;
}
	
