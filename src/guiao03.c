#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"

// KING VALUE (mod 16) == 14

// verifica se uma carta está presente na mão do jogador
int pertenceMao(wchar_t jogadaAtual[], wchar_t maoCartas[])
{
    int r = 0;
    for(int j; jogadaAtual[j] != 0; j++)
        for (int i = 0; maoCartas[i] != '\0'; i++)
            r += comparaCartas(jogadaAtual[j], maoCartas[i]);

    return (r == wcslen(jogadaAtual));
}

int passoJogada(wchar_t jogadasAnteriores[100], int numJogadasAnteriores)
{
    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
        if  (jogadasAnteriores[i] != "PASSO") return 0; // (jogadasAnteriores[i][0] == 'P')
    
    return 1;
}

void retirarJogada(wchar_t jogadaAtual[], wchar_t maoCartas[])
{

}

int tipoIgual(wchar_t jogadaAnterior[], wchar_t jogadaAtual[])
{
    if (conjunto(jogadaAtual, wsclen(jogadaAtual)) && conjunto(jogadaAnterior, wsclen(jogadaAtual)) ||
        seq(jogadaAtual, wsclen(jogadaAtual), 1)   && seq(jogadaAnterior, wsclen(jogadaAtual), 1)   ||
        seq(jogadaAtual, wsclen(jogadaAtual)/2, 2) && seq(jogadaAnterior, wsclen(jogadaAtual)/2, 2)   )
        
}

int combinacaoSuperior(wchar_t jogadasAnteriores[100], wchar_t jogadaAtual[], int numJogadasAnteriores)
{
    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
        if  (jogadasAnteriores[i] == "PASSO") continue;
        else
        {
            if ()
        }
    return 0;

}

void teste(wchar_t maoCartas[], wchar_t jogadasAnteriores[100], wchar_t jogadaAtual[], int numJogadasAnteriores)
{
    if (pertenceMao(jogadaAtual, maoCartas))
    {
        if(numJogadasAnteriores == 0 || passoJogada(jogadasAnteriores, numJogadasAnteriores))
        {
            if (conjunto(jogadaAtual, wsclen(jogadaAtual)) ||
                seq(jogadaAtual, wsclen(jogadaAtual), 1)   ||
                seq(jogadaAtual, wsclen(jogadaAtual)/2, 2)   )
            {
                retirarJogada(jogadaAtual, maoCartas);
                isort(maoCartas, wsclen(maoCartas));
            }
        }
        else if (combinacaoSuperior(jogadasAnteriores, jogadaAtual, numJogadasAnteriores))

    }
}


int main()
{
    setlocale(LC_CTYPE, "C.UTF-8");
    
    int testes, numJogadasAnteriores;
    wchar_t jogadaAtual[100];
    wchar_t maoCartas[100];

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
            assert(wscanf(L"%100ls", &jogadasAnteriores[j][0]) == 0);
        
        // lê e guarda a jogada atual do jogador
        assert(wscanf(L"%100ls", jogadaAtual) != 1);

        // print do teste atual
        wprintf(L"Teste %d\n", i+1);

        teste(maoCartas, jogadasAnteriores, jogadaAtual, numJogadasAnteriores);
        wprintf(L"%100ls\n", maoCartas);
    }
    
    return 0;
}
