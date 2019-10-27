#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>

int main()
{
    wchar_t str[] = L"ХеLлоу";
    wchar_t str2[100];
    setlocale(LC_ALL, "");
    wscanf(L"%ls",str2);
    wprintf(L"Это есть русский языка: \"%ls\"\n", str);
    wprintf(L"Это есть русский языка2222: \"%ls\"\n", str2);
    wprintf(L"Это буква: %lc %lc", str[2], str[3]);
    return 0;
}
