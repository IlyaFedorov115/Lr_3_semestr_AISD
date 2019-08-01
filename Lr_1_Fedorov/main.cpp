#include <iostream>
#include <cstring>
/*
  1) вариант: инициализировать класс после считывания (передавая в конструктор данные)
  2) вариант: считать и функцией put закинуть, после чего просто передавать в chage данные и их менять по ходу
  3) вариант: просто прямо main записывать public данные
*/


using namespace std;

class Vector {
  int* data;
  int len;
  int alpha;
  public:
     Vector();
     void print_vector();
     void change_F(int);
     void put_data(int , int*);
};

Vector::Vector(){
    data = new int;
    len = 1;
}

void Vector::put_data(int x, int* arr){
    data = new int[x];
    len = alpha = x;
    for (int i = 0; i < len; i++){
        data[i] = arr[i];
    }
}

void Vector::print_vector(){
    cout<<"Обработанный вектор = (";
    for (int i = 0; i < len; i++)
    {
         cout << data[i];
         if(i != (len-1)) cout<<",";
         len--;
    }
      cout<<")"<<endl;
}

void Vector::change_F(int start){
    if (alpha == 1) return;
    if (alpha == 2) 
        if (data[start+1] < data[start])
        {
          int tmp = data[start];
          data[start] = data[start+1];
          data[start+1] = tmp;
        }
    if (alpha > 2){
        if (alpha % 2 == 1){
            alpha = alpha/2 + 1;
            change_F(start);
            alpha = alpha/2;
            change_F(start+alpha);
        }else {
            alpha = alpha/2;
            change_F(start);
            change_F(start+alpha);
        }
    }    
}



int main()
{
    cout<<"Hello World\n";
    Vector vector;
    char exit_str[20];
    do 
     {
        char str[10];
        int len;
        cout<<"Введите длину вектора: ";
        fgets(str, sizeof(str), stdin);
        while (sscanf(str, "%d", &len) != 1) {
            cout << "Ошибка ввода. Попробуйте еще раз:";
            fgets(str, sizeof(str), stdin);
        }

        int arr[len];
        cout << "Введите вектор \n";
        for (int i = 0;i < len;i++){
            cout << i+1 << "число:";
            fgets(str, sizeof(str), stdin);
            while (sscanf(str, "%d", &arr[i]) != 1) {
                cout << "Ошибка ввода. Попробуйте ещё:";
                fgets(str, sizeof(str), stdin);
            }
        }
        vector.put_data(len, arr);
        vector.change_F(0);
        vector.print_vector();
        cout << "Нажмите ok для продолжения \n";
        fgets(exit_str,sizeof(exit_str), stdin);
        cout<<"\n";
        fgets(str, sizeof(str), stdin);
     }
     while (strcmp(exit_str,"ok") == 0);

    return 0;
}
