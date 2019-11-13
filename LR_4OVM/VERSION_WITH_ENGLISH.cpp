#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <wchar.h>
#include <stdio.h>
#include <windows.h>
#define Nmax 80

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 
    char buff[Nmax];
    char message[Nmax] = "";
	char map[8] = {'А', 'В', 'С', 'Е', 'A', 'B', 'C', 'E'};
    printf("\nПрограмма Федоров И.А. по лаб.раб.№4  по дисциплине");
    printf("\n\tОрганизация и функционирование аппаратных и");
    printf("\n\t\tпрограммных  средств  ЭВМ");
    printf("\nЗадание: Инвертировать введенные во входной строке цифры в шестнадцатиричной системе счисления (СС) и преобразование строчных русские буквы в заглавные.\n\n");
	printf("\nВведете строку: ");
    fgets(buff,Nmax, stdin);
    
	int n = strlen(buff); //или нет
    
  _asm{
		 mov ecx, n 
		 lea esi,buff         
		 lea edi,message       
      for_: 
		 lodsb 
		 cmp al,'А'  ///////////////////////////////////////
		// jb Else_
		 jb Is_a
		 cmp al, 'а'   // 0A0H  <а 224     
		 jb Else_if        ////////////////////////////////////////////////////////////////////
		 cmp al, 'я'   // 0F7H  я   255
		 ja Write	   
	     sub al, 32    //50H    Регистр   32
		 //jmp Write 
		 jmp Else_if
      Is_a:
		 cmp al, 'a'
         jb Else_
		 cmp al, 'f'
		 ja Else_
		 sub al, 32 // 56
		 jmp Else_
		 

      Else_if:
		 cmp al, 'А'
		 jne nexta
         mov al, 'A'
		 jmp Else_
       nexta:
		 cmp al, 'В'
		 jne nextb
		 mov al, 'B'
		 jmp Else_
	   nextb:	 
		 cmp al, 'Е'
		 jne nexte
		 mov al, 'E'
		 jmp Else_
       nexte:
		 cmp al, 'С'
		 jne Write
		 mov al, 'C'
      Else_:
		 cmp al, 'F'      //английские  46H
		 ja Write         // >F
		 cmp al, 'A'      // <A 41H
		 jb Number
		 sub al, 37H
		 xor al, 0Fh      
		 add al,'0'  
		 jmp Write    
		Number:	
		 cmp al, '0'    //30h  39h
		 jb Write       //не 0-9
		 cmp al, '9'
		 ja Write   
	   Invers:
	    // and al,0fh
		 sub al,'0'
		 xor al,0Fh     
         add al,'0'          
         cmp al,'9'     
         jle Write           // '0'-'9'
         add al,7    
	     jmp Write

      Write:
	    stosb
	    loop for_
	 }
     

    printf("\nВыходная строка: %s", message);
    FILE *fp;
    char* file = "result.txt";
    if ((fp = fopen(file, "w+")) == NULL)
     {
        printf("\nНе удалось открыть файл");
        getchar();
        return 0;
     }
	 fprintf(fp,"Результат: %s",message);
     fclose(fp);
	 printf("\nНажимите enter");
     getchar();
     
     
     
    return 0;
}
