#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <wchar.h>
#include <stdio.h>
#define Nmax 80

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"\nПрограмма Федоров И.А. по лаб.раб.№4  по дисциплине");
    wprintf(L"\n\tОрганизация и функционирование аппаратных и");
    wprintf(L"\n\t\tпрограммных  средств  ЭВМ");
    wprintf(L"\nЗадание: Инвертировать введенные во входной строке цифры в шестнадцатиричной системе\nсчисления (СС) и преобразовать строчных русские буквы в заглавные.\n\n");
   
    wchar_t str[] = L"ХеLлоу";
    wchar_t str2[100];
    //setlocale(LC_ALL, "");
    fgetws(str2,Nmax, stdin);
    
  //  wscanf(L"%ls",str2);
    wprintf(L"Это есть русский языка: \"%ls\"\n", str);
    wprintf(L"Это есть русский языка2222: \"%ls\"\n", str2);
    wprintf(L"Это буква: %lc %lc", str[2], str[3]);
    
    
     __asm__( "");
     
     
    
    
    
    FILE *fp;
    char* file = "result.txt";
    if ((fp = fopen(file, "w+")) == NULL)
     {
        wprintf(L"\nНе удалось открыть файл");
        getchar();
        return 0;
     }
     fwprintf(fp, str2);
  // открыть файл удалось
      // требуемые действия над данными
     fclose(fp);
    
     
     
     
    return 0;
}
