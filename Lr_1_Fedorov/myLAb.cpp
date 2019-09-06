#include <iostream>
#include <cstring>

using namespace std;


class Vector {
 public:
    int* data;
    int size;
// объявлением другом, если закрою массив    
    friend ostream &operator<<(ostream &stream, Vector obj);
};


// перегрузка оператора вывода 

ostream &operator<<(ostream &stream, Vector obj){
    int i = 0;
    for (i; i < sizeof(obj)/sizeof(obj.data[0])-1 ; i++)
    {
        stream << obj.data[i] << ", ";
    }
    stream << obj.data[i] << "\n";
    return stream;
}




void put_from_file(const char *fileName, Vector &obj){
    char ch;
    int count = 0;
    int i = 0;
    ifstream in(fileName, ios::in | ios::binary);
    if (!in){
        cout << "Не удается открыть файл.\n";
        return 1;
    }
    while (in.get(ch))
       count++;
    obj.data = new int[count];
    in.seekp(ios::beg);
    while (in){
        in.get(ch);
        if(in && (ch <='9') && (ch >= '1')) obj.data[i++] = ch; // как сделать динамическую память
    }
    
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


void change_vector(Vector &vector, int i , int len){
    if(len > 2){
        if(len % 2 == 1){
            change_vector(vector,i,len/2+1);
            change_vector(vector,i + len/2 ,len/2);
        }else{
             change_vector(vector,i,len/2);
             change_vector(vector,i + len/2,len/2);
        }
    }

    if(len == 2 && (vector.data[i+1] < vector.data[i])){
        int x = vector.data[i];
        vector.data[i] = vector.data[i+1];
        vector.data[i+1] = x;
    }

    if(len == 1) return;
}

int is_digit(char* str){
    for (int i = 0; i < strlen(str) ; i++){
        if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
}


int main(int argc, char* argv[]) // на всякий случай
{
    
    char ch;
    if(argc!=2){
        cout << "Применение: имя_программы <имя_файла>\n";
        return 1;
    }
    
    
    
  
    return 0;
}
