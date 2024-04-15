#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"

// KING VALUE (mod 16) = 14

wchar_t teste(wchar_t maoCartas, wchar_t jogadasAnteriores[100], wchar_t jogadaAtual, int numJogadasAnteriores)
{
    
}

int main()
{
    setlocale(LC_CTYPE, "C.UTF-8");

    int testes, numJogadasAnteriores;
    wchar_t maoCartas[100], jogadaAtual[100];

    // lê o número de testes que vão ser lidos
    assert(wscanf(L"%d", &testes) != 1); 

    // itera para cada teste
    for (int i = 0; i < testes; i++)
    {
        // lê e guarda o número de jogadas passadas que vão ser lidas
        assert(wscanf(L"%d", &numJogadasAnteriores) != 1);

        // array de jogadas passadas
        wchar_t jogadasAnteriores[numJogadasAnteriores][100];

        // lê e guarda as cartas do jogador
        assert(wscanf(L"%100ls", maoCartas) != 1);
        
        // lê e guarda as jogadas anteriores (linha a linha)
        for (int j = 0; j < numJogadasAnteriores; j++)
        {
            assert(wscanf(L"%100ls", &jogadasAnteriores[j][0]) == 0);
        }


        // print do teste atual
        wprintf(L"Teste %d\n", i+1);
        teste(maoCartas, jogadasAnteriores, jogadaAtual, numJogadasAnteriores);
        wprintf(L"%100ls\n", maoCartas);
    }

    return 0;
}