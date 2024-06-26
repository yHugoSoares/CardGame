#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "functions.h"

// KING VALUE (mod 16) == 14

// verifica se uma carta está presente na mão do jogador
int pertenceMao(wchar_t jogadaAtual[], wchar_t maoCartas[])
{
    long unsigned int r = 0;
    for(int j = 0; jogadaAtual[j] != 0; j++)
        for (int i = 0; maoCartas[i] != '\0'; i++)
            r += comparaCartas(jogadaAtual[j], maoCartas[i]);

    return (r == wcslen(jogadaAtual));
}

void retirarJogada(wchar_t jogadaAtual[], wchar_t maoCartas[])
{
    wchar_t temp[wcslen(maoCartas)];
    int k = 0;
    for(long unsigned int i = 0; i < wcslen(maoCartas); i++)
    {
        for (long unsigned int j = 0; j < wcslen(jogadaAtual); j++)
        {
            int naoEJogado = 1;
            if (maoCartas[j] == jogadaAtual[i]) naoEJogado = 0;
            if (naoEJogado)
            {
                temp[k++] = maoCartas[j];            
            }
        }
    }
    for(long unsigned int i = 0; i < wcslen(maoCartas); i++) maoCartas[i] = temp[i];
}

// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
int jogadaSuperior(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    int tipoIgual = 0;
    int tamanhoIgual = 0;
    int valorSuperior = 0;

    if ( (conjunto(jogadaAtual, wcslen(jogadaAtual)) && conjunto(jogadaAnterior, wcslen(jogadaAtual))) ||
         (seq(jogadaAtual, wcslen(jogadaAtual), 1)   && seq(jogadaAnterior, wcslen(jogadaAtual), 1))   ||
         (seq(jogadaAtual, wcslen(jogadaAtual)/2, 2) && seq(jogadaAnterior, wcslen(jogadaAtual)/2, 2))    )
            tipoIgual = 1;

    if (wcslen(jogadaAtual) == wcslen(jogadaAnterior))
            tamanhoIgual = 1;

    if (comparaCartas(maiorCarta(jogadaAtual, wcslen(jogadaAtual)), maiorCarta(jogadaAnterior, wcslen(jogadaAnterior))))
            valorSuperior = 1;

    if (tipoIgual && tamanhoIgual && valorSuperior) return 1;
    else return 0;
}


// combinacaoValida que testa se a jogada recebida como argumento é conjunto, seq ou dupla seq
int combinacaoValida(wchar_t jogadaAtual[])
{
    // Verifica se é um conjunto
    if (conjunto(jogadaAtual, wcslen(jogadaAtual)))
        return 0;
    // Verifica se é uma sequência
    if (seq(jogadaAtual, wcslen(jogadaAtual), 1))
        return 0;
    // Verifica se é uma dupla sequência
    if (seq(jogadaAtual, wcslen(jogadaAtual) / 2, 2))
        return 0;

    return 1;
}


int jogadaValida(wchar_t jogadasAnteriores[][100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
        // verifica se a jogada anterior é "PASSO" e se a jogada atual é uma combinação válida
        if  (jogadasAnteriores[i][0] == 'P' && combinacaoValida(jogadaAtual)) continue;
        // verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
        else if (jogadaSuperior(jogadaAtual, jogadasAnteriores[i])) break;
        // se nenhuma das anteriores se verificar a jogada não é válida
        else return 0;
    
    return 1;
}

void teste(wchar_t maoCartas[], wchar_t jogadasAnteriores[][100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
    // Verifica se as cartas jogadas pertencem à mão do jogador e são uma jogada válida
    if (pertenceMao(jogadaAtual, maoCartas) && jogadaValida(jogadasAnteriores, numJogadasAnteriores, jogadaAtual))
    {
        isort(maoCartas, wcslen(maoCartas));
        retirarJogada(maoCartas, jogadaAtual);
    }
}

void escrevecarta(wchar_t maoCartas[], int numCartas) // escreve as cartas com espacos entre elas
{
    for (int i = 0; i < numCartas; i++)
    {
        wprintf(L"%lc ", maoCartas[i]);
    }
    wprintf(L"\n");
}


int main()
{
    setlocale(LC_CTYPE, "C.UTF-8");
    
    int testes, numJogadasAnteriores;
    wchar_t jogadaAtual[100];
    wchar_t maoCartas[100];

    // lê o número de testes que vão ser lidos
    assert(wscanf(L"%d", &testes) == 1); 

    // itera para cada teste
    for (int i = 0; i < testes; i++)
    {
        // lê e guarda o número de jogadas passadas que vão ser lidas
        assert(wscanf(L"%d", &numJogadasAnteriores) == 1);

        // array de jogadas passadas
        wchar_t jogadasAnteriores[numJogadasAnteriores][100];

        // lê e guarda as cartas do jogador
        assert(wscanf(L"%100ls", maoCartas) != 0);
        
        // lê e guarda as jogadas anteriores (linha a linha)
        for (int j = 0; j < numJogadasAnteriores; j++)
            assert(wscanf(L"%100ls", &jogadasAnteriores[j][0]) != 0);
        
        // lê e guarda a jogada atual do jogador
        assert(wscanf(L"%100ls", jogadaAtual) != 0);

        // print do teste atual
        wprintf(L"Teste %d\n", i+1);

        // loop que imprime a mao com espaços
        teste(maoCartas, jogadasAnteriores, numJogadasAnteriores, jogadaAtual);
        escrevecarta(maoCartas, wcslen(maoCartas));
        //proximo teste
        retirarJogada(maoCartas, jogadaAtual);
        escrevecarta(maoCartas, wcslen(maoCartas));
        
    }
    
    return 0;
}
