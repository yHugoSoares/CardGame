#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>

wchar_t maiorcarta(wchar_t cartas[], int numCartas) {
    // ordem dos naipes: espadas < copas < ouros < paus
    wchar_t atualMaiorCarta = cartas[0];
    
    for (int i = 1; i < numCartas ; i++) { // encontra a maior carta
        if (cartas[i]%16 > atualMaiorCarta%16) // se a carta for maior
            atualMaiorCarta = cartas[i];
        else if (cartas[i]%16 == atualMaiorCarta%16 && cartas[i] > atualMaiorCarta) // se carta for igual e naipe maior
            atualMaiorCarta = cartas[i];
    }

    return atualMaiorCarta;
}

int conjunto(wchar_t cartas[])
{
    for (int i = 0; cartas[i] != '\0'; i++)
    {
        if (cartas[i] % 16 != cartas[0] % 16)
        {
            return 0; // as cartas nao tem o mesmo valor
        }
    }
    return 1; // todas tem o mesmo valor 
}

int seq(wchar_t cartas[])
{
    int numCartas = wcslen(cartas), aux = 0;
    wchar_t primeiraCarta = cartas[0];
    for (int i = 0; i < numCartas - 1; i++) 
    {
        for (int j = 0; i < numCartas - 1; j++)
        {
            if ((cartas[i + j] + 1) % 16 == primeiraCarta % 16) 
            {
                aux++;
                primeiraCarta = cartas[i + j];
            }
        }
    }
    if (aux != numCartas - 1) return 0;
    return 1; // Todas as cartas estão em ordem na sequência
}

int dseq(wchar_t cartas[])
{
    wchar_t cartasCompare = cartas[0];
    for (int i = 1; cartas[i] != '\0'; i++)
    {
        if (cartasCompare != cartas[i]) return 0; // nao tem o mesmo valor 
        cartasCompare = cartas[i];
        i++;
    }
    return 1; // formam dupla sequencia 
}

int main()
{
    setlocale(LC_ALL, "");
    
    int l;
    wchar_t cartas[100];
    
    if (wscanf(L"%d\n", &l) == 0) return 0;
    
    for (int i = 0; i < l; i++)
    {
        if (wscanf(L" %100ls", cartas) == 0) return 0;

        int numCartas = wcslen(cartas);
        
        if (conjunto(cartas) == 1)
            wprintf(L"conjunto com %d cartas onde a carta mais alta é: %lc\n", numCartas, maiorcarta(cartas, numCartas));

        else if (dseq(cartas) == 1)
            wprintf(L"sequência com %d cartas onde a carta mais alta é: %lc\n", numCartas, maiorcarta(cartas, numCartas));

        else if (seq(cartas) == 1)
            wprintf(L"dupla sequência com %d cartas onde a carta mais alta é: %lc\n", numCartas/2, maiorcarta(cartas, numCartas));

        else
            printf("Nada!\n");
    }
    return 0;
}