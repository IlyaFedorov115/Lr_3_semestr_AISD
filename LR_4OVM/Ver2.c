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
		 cmp al, 224   // 0A0H  <а      
		 jb Else_
		 cmp al, 255   // 0F7H  я
		 ja Write	   
	     sub al, 32    //50H    Регистр
		 jmp Write       
	   
      Else_:
		 cmp al, 46H      //английские
		 ja Write         // >F
		 cmp al, 41H      // <A
		 jb Number
		 sub al,37H
		 xor al,0Fh      
		 add al,'0'  
		 jmp Write    
		Number:	
		 cmp al, 30H
		 jb Write       //не 0-9
		 cmp al, 39H
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
     getchar();
     
     
     
    return 0;
}
