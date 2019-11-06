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
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
    char buff[Nmax];
    char message[Nmax] = "";
    
    printf("\nПрограмма Федоров И.А. по лаб.раб.№4  по дисциплине");
    printf("\n\tОрганизация и функционирование аппаратных и");
    printf("\n\t\tпрограммных  средств  ЭВМ");
    printf("\nЗадание: Инвертировать введенные во входной строке цифры в шестнадцатиричной системе счисления (СС) и преобразование строчных русские буквы в заглавные.\n\n");

    fgets(buff,Nmax, stdin);
    
    printf("Это есть русский языка: %s \n", buff);
  //  printf("Это есть русский языка2222: \"%ls\"\n", buff);
    printf("Это буква: %c %c %c %c", buff[3],buff[4],buff[0],buff[2]);
    
	int n = strlen(buff)-1;//или нет
    
  _asm{
		 mov ecx, n 
		 lea esi,buff         
		 lea edi,message       
		                                    // mov bx,0
											// mov bp,0
   for_: 
		 lodsb 
		 cmp al, 224   // 0A0H  а      
		 jb Else_
		 cmp al, 255   // 0F7H  я
		 ja Write	
		 // jg Else_ 
		//              cmp al, 0AFH
		               // JBE  Part1      
	     sub al, 32    //50H    Регистр
		 jmp Write       
		                 //              Part1: 
		                             //sub al,20H
		                            //jmp Write   
	  Else_:
		 cmp al, 46H      //английские
		 ja Write         //jg   >F
		 cmp al, 41H      //    <A
		 jb Number
		// jmp Ver2
		 sub al,37H
		 xor al,0Fh         //not al 
		 add al,'0'   //????????????????????
		 jmp Write      //с A-F при инвертировании все окей, просто записываем
		Number:	
		 cmp al, 30H
		 jb Write       //не 0-9
		 cmp al, 39H
		 ja Write    //jg
		                 //jmp Invers    
	    Invers:
	     //sub al,'0'   //30h
	     AND AL,0fh
		 xor al,0Fh         //not al 
	     //изменения                   //	 add al,'0'         //?????????????????????????????????????????
         add al,'0'            //  ;Прибавляем символ '0' (код 0x30)
         cmp al,'9'            //  ;Сравнение с символом '9' (код 0x39)
         jle Write           //  ;Если получилось '0'-'9', то выход
         add al,7              //  ;Прибавляем ещё 7 для символов 'A'-'F'
	     jmp Write
	//  Ver2:
	 //  sub al,37H
	 //  not al
	 //  jmp Write
    Write:
	  stosb
      //;//mov ds:[edi], ax 
      //;dec cx
	  //;inc di
	  //;inc si
	  loop for_
      //cmp cx, 0
      //jne for_
	 }
     

    printf("\n\n%s", message);
    FILE *fp;
    char* file = "result.txt";
    if ((fp = fopen(file, "w+")) == NULL)
     {
        wprintf(L"\nНе удалось открыть файл");
        getchar();
        return 0;
     }
  // открыть файл удалось
      // требуемые действия над данными
     fclose(fp);
     getchar();
     
     
     
    return 0;
}
