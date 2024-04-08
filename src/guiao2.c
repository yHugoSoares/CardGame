#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>

// função que verifica se as sequencias são do mesmo tipo e têm o mesmo tamanho
// função ordena por ordem crescente as cartas numa linha (e adiciona um espaço entre as cartas?)
// função que ordena por ordem crescente as sequências dentro de um teste


int main() 
{    
    setlocale(LC_CTYPE, "C.UTF-8");
    
    int testes;
    int linhas;

    if (wscanf(L"%d", &testes) != 1) return 1; // lê o número de testes que vão ser lidos

    for (int i = 0; i < testes; ++i){ // itera para cada teste

    if (wscanf(L"%d", &linhas) != 1) return 1; // lê o número de linhas que vão ser lidas
        
        int primeiro_comprimento;

        for (int j = 0; j < linhas; ++j){ // itera para cada linha

        int comprimento;

        wchar_t cartas[100]; // assume-se que cada conjunto de cartas tem no máximo 100 elementos

        if (wscanf(L"%100ls", cartas) == 0) return 1; // lê um conjunto de cartas

        comprimento = wcslen (cartas);
        
        if (j == 0) primeiro_comprimento = comprimento;
        else if (primeiro_comprimento != comprimento){
            printf ("Combinações não iguais!");
            break;
        }


        if (conjunto(cartas, numCartas) == 1)
            wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n",
                    numCartas, maiorCarta(cartas, numCartas));
        else if (seq(cartas, numCartas, 1) == 1)
            wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n",
                    numCartas, maiorCarta(cartas, numCartas));
        else if (seq(cartas, numCartas/2, 2) == 1)
            wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n",
                    numCartas/2, maiorCarta(cartas, numCartas));
        else wprintf(L"Nada!\n");

    }
    }
    return 0;
}