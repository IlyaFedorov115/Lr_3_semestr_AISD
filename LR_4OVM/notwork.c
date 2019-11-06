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
    setlocale(LC_ALL, "");
    wprintf(L"\nПрограмма Федоров И.А. по лаб.раб.№4  по дисциплине");
    wprintf(L"\n\tОрганизация и функционирование аппаратных и");
    wprintf(L"\n\t\tпрограммных  средств  ЭВМ");
    wprintf(L"\nЗадание: Инвертировать введенные во входной строке цифры в шестнадцатиричной системе\nсчисления (СС) и преобразовать строчных русские буквы в заглавные.\n\n");
   
    wchar_t buff[] = L"ХеLлоу";
    wchar_t message[100];
    //setlocale(LC_ALL, "");
    fgetws(message,Nmax, stdin);
    
  //  wscanf(L"%ls",str2);
    wprintf(L"Это есть русский языка: \"%ls\"\n", message);
    wprintf(L"Это есть русский языка2222: \"%ls\"\n", message);
    wprintf(L"Это буква: %lc %lc", message[2], buff[3]);
    
	int n = wcslen(message);

    
     _asm{
		 mov cx, 10  
		 lea esi,buff         
		 lea edi,message       
		 mov bx,0
		 mov bp,0
	  for_: 
		 mov ax,ds:[esi]
		 cmp al, 0A0H        
		jb Else
		cmp al, 0F7H
		jg Else 
		  cmp al, 0AFH
		 JBE  Part1      
	    sub al,50H
		 jmp Write       
		 Part1: 
		 sub al,20H
		 jmp Write   
	  Else:
		 cmp al, 46H
		jg Write      
		 cmp al, 41H   
		 jb Number
		jmp Ver2	 
		Number:	
		 cmp al, 30H
		jb Write
		cmp al, 39H
		jg Write
		jmp Invers    
	  Invers:
	   sub al,'0'  
	   not al   
	   jmp Write
	  Ver2:
	   sub al,37H
	   not al
	   jmp Write
    Write:
      mov ds:[edi], ax 
      dec cx
	  inc di
	  inc si
      cmp cx, 0
      jne for_
	 }
     

    
    FILE *fp;
    char* file = "result.txt";
    if ((fp = fopen(file, "w+")) == NULL)
     {
        wprintf(L"\nНе удалось открыть файл");
        getchar();
        return 0;
     }
     fwprintf(fp, message);
  // открыть файл удалось
      // требуемые действия над данными
     fclose(fp);
     getchar();
     
     
     
    return 0;
}
