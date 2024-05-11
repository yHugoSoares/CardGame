#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "functions.h"

void ordenaCartas(int numCartas, wchar_t jogada[])
{	
    int i, j;
    wchar_t aux;
    for (i = 0; i < numCartas; i++) 
    {
        aux = jogada[i];	
        for (j = i; j > 0 && comparaCartas(jogada[j-1],aux); j--)
            jogada[j] = jogada[j-1];	
        jogada[j] = aux;	
    }	
}

int comparaJogadas(wchar_t c1[], wchar_t c2[], int l1, int l2)
{
	if (wcslen(c1) == 0 || wcslen(c2) == 0)
		return 0;
    if (wcslen(c1) > wcslen(c2))
        return 1;
	else if (conjunto(c1, wcslen(c1)) && !conjunto(c2, wcslen(c2)))
		return 0;
	else if (seq(c1, wcslen(c1), 1) && seq(c2, wcslen(c2), 2))
		return 0;
	else if (comparaCartas(c1[l1],c2[l2]) && wcslen(c1) == wcslen(c2))
    {
		return 1;
    }
	else if (c1[l1] == c2[l1])
		return comparaJogadas(c1, c2, l1+1, l2+1);
	return 0;
}

void ordenaJogadas(int numJogadas, int numCartas, wchar_t cartas[][numCartas]) // implementação do bubble sort para ordenar as sequências
{	
    int i, j;
    for (i = numJogadas; i > 0; i--)
        for (j = 1; j < i; j++)	
            if (comparaJogadas(cartas[j-1], cartas[j], 0, 0))
            {
                wchar_t aux[numCartas];
                wcscpy(aux, cartas[j]);
	            wcscpy(cartas[j], cartas[j-1]);
	            wcscpy(cartas[j-1], aux);
            }
}

int tudoReis(wchar_t jogada[]) 
{
    int tam = wcslen(jogada);

    for(int i = 0; i < tam; i++) 
        if (jogada[i] % 16 != 14) return 0;

    return 1;
}

// combinacaoValida que testa se a jogada recebida como argumento é conjunto, seq ou dupla seq
int combinacaoValida(wchar_t jogadaAtual[])
{
	// Verifica se é um conjunto
	if (conjunto(jogadaAtual, wcslen(jogadaAtual)))
		return 1;
	// Verifica se é uma sequência
	if (seq(jogadaAtual, wcslen(jogadaAtual), 1))
		return 1;
	// Verifica se é uma dupla sequência
	if (seq(jogadaAtual, wcslen(jogadaAtual), 2))
		return 1;

	return 0;
}

// testa casos especiais
int casosEspeciais(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    int tamanhoJogada = wcslen(jogadaAtual);
    int tamanhoAnterior = wcslen(jogadaAnterior);
    
    if (tudoReis(jogadaAnterior))
    {
        if (tamanhoAnterior == 1 && conjunto(jogadaAtual, tamanhoJogada) && tamanhoJogada == 4)
            return 1;
        else if (tamanhoAnterior == 1 && seq(jogadaAtual, tamanhoJogada, 2) && tamanhoJogada/2 == 3)
            return 1;
        else if (tamanhoAnterior == 2 && seq(jogadaAtual, tamanhoJogada, 2) && tamanhoJogada/2 == 4)
            return 1;
        else if (tamanhoAnterior == 3 && seq(jogadaAtual, tamanhoJogada, 2) && tamanhoJogada/2 == 5)
            return 1;
    }

    return 0;
}

// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
int jogadaSuperior(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    if (tudoReis(jogadaAnterior))
        return casosEspeciais(jogadaAtual, jogadaAnterior);
    
    int tamanhoJogada = wcslen(jogadaAtual);
    int tamanhoAnterior = wcslen(jogadaAnterior);
    int tipoIgual = 0;
    int valorSuperior = 0;

    if (conjunto(jogadaAtual,tamanhoJogada) && conjunto(jogadaAnterior, tamanhoAnterior))
        tipoIgual = 1;
    else if (seq(jogadaAtual, tamanhoJogada, 1) && seq(jogadaAnterior, tamanhoAnterior, 1))
        tipoIgual = 1;
    else if (seq(jogadaAtual, tamanhoJogada, 2) && seq(jogadaAnterior, tamanhoAnterior, 2))
        tipoIgual = 1;

    if (comparaCartas(maiorCarta(jogadaAtual, tamanhoJogada), maiorCarta(jogadaAnterior, tamanhoAnterior)))
        valorSuperior = 1;

    if (tipoIgual && valorSuperior) return 1;
    else return 0;
}

int jogadaValida(wchar_t jogadaAnterior[], wchar_t jogadaAtual[])
{
	// verifica se a jogada anterior é "PASSO" e se a jogada atual é uma combinação válida
	if  (jogadaAnterior[0] == 'P' && combinacaoValida(jogadaAtual)) return 1;
	// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
	else if (jogadaSuperior(jogadaAtual, jogadaAnterior)) return 1;
	// se nenhuma das anteriores se verificar a jogada não é válida
	else return 0;
}

void imprimeJogada(int numCartas, wchar_t jogada[])
{
	for (int i = 0; i < numCartas; i++)
	{
        if (i == numCartas - 1)
            wprintf(L"%lc", jogada[i]);
		else
            wprintf(L"%lc ", jogada[i]);
	}
	wprintf(L"\n");
}

void imprimeJogadas(int numJogadas, int numCartas, wchar_t jogadas[][numCartas])
{
	if (numJogadas == 0) wprintf(L"PASSO\n");

    for (int i = 0; i < numJogadas; i++)
        imprimeJogada(wcslen(jogadas[i]), jogadas[i]);
}

// Function to generate all substrings of a given word of length N
void generateSubsets(const wchar_t *word, int N, int *atual, int numCartas,
                     wchar_t jogadas[][numCartas], wchar_t jogadaAnterior[])
{
    int len = wcslen(word);

    // Buffer de caracteres para reutilização
    wchar_t substring[N + 1];

    // Pré-computar o comprimento do word
    int wordLen = len;

    // Loop para iterar sobre todas as combinações possíveis de caracteres com comprimento N
    for (int i = 0; i < (1 << len); i++) 
    {
        // Contar o número de bits definidos em 'i'
        int count = __builtin_popcount(i); // Função de contagem de bits

        // Se a contagem for igual a N, gerar a substring
        if (count == N) 
        {
            int index = 0;
            for (int j = 0; j < wordLen; j++) 
            {
                if (i & (1 << j)) substring[index++] = word[j];
            }
            substring[index] = L'\0'; // Terminar a substring com null-character

            // Verificar e manipular a substring conforme necessário
            if (index == N && jogadaValida(jogadaAnterior, substring)) 
            {
                ordenaCartas(N, substring);
                wcscpy(jogadas[(*atual)++], substring);
            }
        }
    }
}

void geraJogadas(wchar_t mao[], wchar_t jogadaAnterior[])
{
    int tamMao = wcslen(mao);
    int tamAnterior = wcslen(jogadaAnterior);

    if (tamMao < tamAnterior)
    {
        wprintf(L"PASSO\n");
        return;
    }
    
    wchar_t jogadas[3000][tamMao];
    int atual = 0;
    int casoEspecial = tudoReis(jogadaAnterior);

    if (!casoEspecial)
        generateSubsets(mao, tamAnterior, &atual, tamMao, jogadas, jogadaAnterior);
    else
    {
        if (tamAnterior == 1) // 1 rei
        {
            generateSubsets(mao, tamAnterior, &atual, 4, jogadas, jogadaAnterior); // conjunto 4 cartas
            generateSubsets(mao, tamAnterior, &atual, 6, jogadas, jogadaAnterior); // duplaSeq 3 cartas
        }
        else if (tamAnterior == 2) // 2 reis
            generateSubsets(mao, tamAnterior, &atual, 8, jogadas, jogadaAnterior); // duplaSeq 4 cartas
        else if (tamAnterior == 3) // 3 reis
            generateSubsets(mao, tamAnterior, &atual, 10, jogadas, jogadaAnterior); // duplaSeq 5 cartas
    }


    ordenaJogadas(atual, tamMao, jogadas);
    imprimeJogadas(atual, tamMao, jogadas);
}

int main()
{
  setlocale(LC_CTYPE, "C.UTF-8");
  
  int testes;

  wchar_t jogadaAnterior[100];
  wchar_t mao[100]; 

  // lê o número de testes que vão ser lidos
  assert(wscanf(L"%d", &testes) == 1);

  // itera para cada teste
  for (int i = 0; i < testes; i++)
  {
    // lê e guarda a jogada anterior
    assert(wscanf(L"%100ls", jogadaAnterior) != 0);

    // lê e guarda a mao do jogador 
    assert(wscanf(L"%100ls", mao) != 0);

    // print do teste atual
    wprintf(L"Teste %d\n", i+1);
    
    // gera todas as permutações possíveis das cartas da mão e coloca-as no array jogadasPossiveis
    geraJogadas(mao, jogadaAnterior);
  }
  
  return 0;
}