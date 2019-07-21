/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
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
     vector();
     void print_vector();
     void change_F();
     void put_data();
};

Vector::Vector(){
    data = new 1;
    len = 1;
    alpha = 1;
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

void Vector::change_F(){
    if (alpha == 1) return;
    if (alpha == 2) 
        if (data[1] < data[0])
        {
          int tmp = data[0];
          data[0] = data[1];
          data[1] = tmp;
        }
    if (alpha > 2){
        if (alpha % 2 == 1){
            change_F()
        }
    }    
}



int main()
{
    cout<<"Hello World";

    return 0;
}
