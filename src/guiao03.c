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
<<<<<<< HEAD
    int resultado = 0;
    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
        if  (jogadasAnteriores[i] == "PASSO") resultado++;// (jogadasAnteriores[i][0] == 'P')
=======
    for (int i = 0; jogadaAtual[i] != '\0'; i++)
    {
        for (int j = 0; maoCartas[j] != '\0'; j++)
        {
            if (maoCartas[j] == jogadaAtual[i]) 
            {
                for (int k = j; maoCartas[k] != '\0'; k++) maoCartas[k] = maoCartas[k + 1];
            }
            break; 
        }
    }
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
>>>>>>> 604c505cfd0c9e40a071791650ec86a1dc11478c
    
    return resultado;
}

void teste(wchar_t maoCartas[], wchar_t jogadasAnteriores[][100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
<<<<<<< HEAD
    for (int i = 0; jogadaAtual[i] != '\0'; i++)
    {
        for (int j = 0; maoCartas[j] != '\0'; j++)
        {
            if (maoCartas[j] == jogadaAtual[i]) 
            {
                for (int k = j; maoCartas[k] != '\0'; k++)
                {
                    maoCartas[k] = maoCartas[k + 1];
                }
                break; 
            }
        }
    }
}

int tipoIgual(wchar_t jogadaAnterior[], wchar_t jogadaAtual[])
{
    if (conjunto(jogadaAtual, wsclen(jogadaAtual)) && conjunto(jogadaAnterior, wsclen(jogadaAtual)) ||
        seq(jogadaAtual, wsclen(jogadaAtual), 1)   && seq(jogadaAnterior, wsclen(jogadaAtual), 1)   ||
        seq(jogadaAtual, wsclen(jogadaAtual)/2, 2) && seq(jogadaAnterior, wsclen(jogadaAtual)/2, 2)   ) return 1; // São do mesmo tipo
        else return 0; // São de tipos diferentes 
        
}

int combinacaoSuperior(wchar_t jogadasAnteriores[100], wchar_t jogadaAtual[], int numJogadasAnteriores)
{
    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
        if  (jogadasAnteriores[i] == "PASSO") continue;
        else
        {
           if (maiorCarta(jogadaAtual,
            wcslen(jogadaAtual)) > maiorCarta(jogadasAnteriores[i],
            wcslen(jogadasAnteriores[i]))) return 1; // Jogada atual é superior
        }
    return 0; // A jogada atual não é superior 

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
        else if (combinacaoSuperior(jogadasAnteriores, jogadaAtual, numJogadasAnteriores));

=======
    // Verifica se as cartas jogadas pertencem à mão do jogador e são uma jogada válida
    if (pertenceMao(jogadaAtual, maoCartas) && jogadaValida(jogadasAnteriores, numJogadasAnteriores, jogadaAtual))
    {
        retirarJogada(jogadaAtual, maoCartas);
        isort(maoCartas, wcslen(maoCartas));
>>>>>>> 604c505cfd0c9e40a071791650ec86a1dc11478c
    }
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
        for (int k = 0; maoCartas[k] != '\0' ; k++) wprintf(L"%100ls ", maoCartas);

        //proximo teste
        printf("\n");
        
    }
    
    return 0;
}
