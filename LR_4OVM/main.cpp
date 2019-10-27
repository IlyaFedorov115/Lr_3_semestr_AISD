#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>

int main()
{
    wchar_t str[] = L"Хеллоу";
    wchar_t str2[100];
    setlocale(LC_ALL, "");
    wscanf(L"%ls",str2);
    wprintf(L"Это есть русский языка: \"%ls\"\n", str);
    wprintf(L"Это есть русский языка2222: \"%ls\"\n", str2);
    return 0;
}
