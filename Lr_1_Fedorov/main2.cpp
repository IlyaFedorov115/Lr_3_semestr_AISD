#include <iostream>
#include <cstring>

using namespace std;

typedef struct Vector {
    int* data;
    int size;
}Vector;

void print_vector(Vector &vector, int len){
 /*   if(vector.size < len) 
        len = vector.size;
  */cout << "Обработанный вектор = (";
    for (int i = 0 ; i < len ; i++){
       cout << vector.arr[i];
       if(i != (len-1)) cout<<",";
    }
    cout<<")"<<endl;
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

    if(len == 2 && (vector.arr[i+1] < vector.arr[i])){
        int x = vector.arr[i];
        vector.arr[i] = vector.arr[i+1];
        vector.arr[i+1] = x;
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
  //  char exit_str[20];
    vect vector;

    do{
        char str[5];
            printf("%s","Введите длину вектора: ");
         fgets(str, sizeof(str), stdin);

        if (is_digit(str)){
            vector.size = atoi(str);
            if (vector.size )
        }


        while (sscanf(str, "%d", &vector.size) != 1) {
            printf("Ошибка ввода. Попробуйте ещё:");
            fgets(str, sizeof(str), stdin);
        }

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

    exit(1);
    return a.exec();
}
