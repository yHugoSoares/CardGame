#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"


int main()
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    wchar_t cartas[10] = {0x1F0A1, 0x1F0A2, 0x1F0A3, 0x1F0A4, 0x1F0A5, 0x1F0A6, 0x1F0A7, 0x1F0A8, 0x1F0A9, 0x1F0AA};
    int numCartas = 10;

    printf("Conjunto: %d\n", conjunto(cartas, numCartas));
    printf("Sequência: %d\n", seq(cartas, numCartas, 1));

    return 0;
}