#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int main()
{
    setlocale (LC_CTYPE, "C.UTF-8");
    wchar_t cartas;
    wscanf(L"%100ls", &cartas);
    int value = cartas%16;
    wprintf(L"%d\n", value);
}