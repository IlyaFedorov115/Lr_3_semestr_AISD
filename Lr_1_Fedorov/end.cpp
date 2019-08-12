/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cstring>


using namespace std;


typedef struct Vector{
    int* data;
    int size;
}Vector;

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


int main()
{
    cout<<"Введите длину вашего вектора: ";
    int len;
    cin >> len;
    cout<<"\n";
    int arr[len];
    for (int i = 0; i<len; i++){
        cout << i+1 << "-e число = ";
        cin >> arr[i];
    }
    Vector vect;
    put_data(vect, arr, len);
    print_vector(vect);
    change_vector(vect,0,len);
    print_vector(vect);
    
    
    do{
        char str[5];
            printf("%s","Введите длину вектора: ");
         fgets(str, sizeof(str), stdin);

        if (is_digit(str)){
            vector.size = atoi(str);
           // if (vector.size )
        }


        while (sscanf(str, "%d", &vector.size) != 1) {
            printf("Ошибка ввода. Попробуйте ещё:");
            fgets(str, sizeof(str), stdin);
        }

        int arr[vector.size];
        vector.data = arr;

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
    
    
    
   // cout << vect.data[2];
    return 0;
}
