#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "functions.h"

void swap2(int numSubString, int len, wchar_t cartas[numSubString][len], int i, int j) // implementação do swap para troca de posição duas sequências
{
    wchar_t aux[len];

    wcscpy(aux, cartas[i]);
	wcscpy(cartas[i], cartas[j]);
	wcscpy(cartas[j], aux);
}

int soma(wchar_t cartas[]){
  int soma = 0;
  for (int i = 0; cartas[i] != '\0'; i++){
    soma += cartas[i];
  }
  return soma;
}

int comparaSeq(wchar_t c1[], int l1, wchar_t c2[], int l2)
{
	if (wcslen(c1) == 0 || wcslen(c2) == 0)
		return 0;

	if (conjunto(c1, wcslen(c1)) && !conjunto(c2, wcslen(c2)))
		return 0;
	else if (seq(c1, wcslen(c1), 1) && seq(c2, wcslen(c2)/2, 2))
		return 0;
	else if (wcslen(c1) > wcslen(c2))
		return 1;
	else if (comparaCartas(c1[l1],c2[l2]))
		return 1;
	else if (c1[l1] == c2[l1])
		return comparaSeq(c1, l1+1, c2, l2+1);
	else
		return 0;
}

void bsort2(int numSubString, int len, wchar_t cartas[numSubString][len]) // implementação do bubble sort para ordenar as sequências
{	
    int i, j;	
    for (i = numSubString; i > 0; i--)	
        for (j = 1; j < i; j++)	
            if (comparaSeq(cartas[j-1], 0, cartas[j], 0))
                swap2(numSubString, len, cartas, j-1, j);
}

void isort2(wchar_t cartas[], int numCartas) // implementação do insertion sort para ordenar as cartas de uma sequência
{	
    int i, j;
    wchar_t aux;
    for (i = 0; i < numCartas; i++) 
    {
        aux = cartas[i];	
        for (j = i; j > 0 && comparaCartas(cartas[j-1],aux); j--)
            cartas[j] = cartas[j-1];	
        cartas[j] = aux;	
    }	
}

void ordena2(int numSubStrings, int len, wchar_t subStrings[numSubStrings][len]) // ordena as sequências e as cartas das sequências por ordem crescente
{
    for (int i = 0; i < numSubStrings; i++)
         isort2(subStrings[i], wcslen(subStrings[i]));
    bsort2(numSubStrings, len, subStrings);
}

// testa casos especiais
int casosEspeciais(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    int tamanhoJogada = wcslen(jogadaAtual);
    int tamanhoAnterior = wcslen(jogadaAnterior);

    int tudoReis = 1;
    for (int i = 0; i < tamanhoAnterior; i++)
        if (jogadaAnterior[i] % 16 != 14) tudoReis = 0;
    
    if (tudoReis)
    {
        if (tamanhoAnterior == 1 && conjunto(jogadaAtual, tamanhoJogada) && tamanhoJogada == 4)
            return 1;
        else if (tamanhoAnterior == 1 && seq(jogadaAtual, tamanhoJogada/2, 2) && tamanhoJogada/2 == 3)
            return 1;
        else if (tamanhoAnterior == 2 && seq(jogadaAtual, tamanhoJogada/2, 2) && tamanhoJogada/2 == 4)
            return 1;
        else if (tamanhoAnterior == 3 && seq(jogadaAtual, tamanhoJogada/2, 2) && tamanhoJogada/2 == 5)
            return 1;
    }

    return 0;
}

// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
int jogadaSuperior(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    if (casosEspeciais(jogadaAtual, jogadaAnterior)) return 1;
    
    int tamanhoJogada = wcslen(jogadaAtual);
    int tamanhoAnterior = wcslen(jogadaAnterior);
    int tipoIgual = 0;
    int tamanhoIgual = 0;
    int valorSuperior = 0;

    if (conjunto(jogadaAtual,tamanhoJogada) && conjunto(jogadaAnterior, tamanhoAnterior))
        tipoIgual = 1;
    else if (seq(jogadaAtual, tamanhoJogada, 1) && seq(jogadaAnterior, tamanhoAnterior, 1))
        tipoIgual = 1;
    else if (seq(jogadaAtual, tamanhoJogada/2, 2) && seq(jogadaAnterior, tamanhoAnterior/2, 2))
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

int jogadaValida(wchar_t jogadaAnterior[100], wchar_t jogadaAtual[])
{
	// verifica se a jogada anterior é "PASSO" e se a jogada atual é uma combinação válida
	if  (jogadaAnterior[0] == 'P' && combinacaoValida(jogadaAtual)) return 1;
	// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
	else if (jogadaSuperior(jogadaAtual, jogadaAnterior)) return 1;
	// se nenhuma das anteriores se verificar a jogada não é válida
	else return 0;
}

void imprimeMao(wchar_t maoCartas[], int numCartas) // escreve as cartas com espacos entre elas
{
	for (int i = 0; i < numCartas; i++)
	{
		wprintf(L"%lc ", maoCartas[i]);
	}
	wprintf(L"\n");
}

int power(int n, int length)
{
	int r = 1;
	for (int i = 0; i < length; i++)
		r *= n;
	return r;
}

// Function to generate all substrings of a given word
void geraSubsets(const wchar_t *word, wchar_t jogadaAnterior[]) 
{
	int len = wcslen(word);
	int numSubstrings = power(2, len) - 1; // Calculate the number of substrings
	wchar_t jogadasPossiveis[numSubstrings][len+1];
	
	// Loop to iterate over all possible substring lengths
	for (int i = 1; i <= numSubstrings; i++) 
	{
		// Convert 'i' to binary representation to determine which characters to include
		int binary = i;
		int j = 0;
		wchar_t *substring = (wchar_t *)malloc((len + 1) * sizeof(wchar_t));
		
		// Loop through each character of the word
		for (int k = len - 1; k >= 0; k--) 
		{
			if (binary & (1 << k)) 
			{
				// If the k-th bit of 'binary' is set, include the corresponding character
				substring[j++] = word[len - k - 1];
			}
		}
		substring[j] = L'\0'; // Null-terminate the substring
		jogadaAnterior = jogadaAnterior;
		wcscpy(jogadasPossiveis[i-1],substring);

		free(substring);
  	}
	
	ordena2(numSubstrings, len, jogadasPossiveis);

	int printed = 0;
	for (int i = 0; i < numSubstrings; i++)
	{
		// if (jogadaValida(jogadaAnterior, jogadasPossiveis[i]))
		// {
			imprimeMao(jogadasPossiveis[i], wcslen(jogadasPossiveis[i]));
			printed = 1;
		// }
	}
	if (!printed)
		wprintf(L"PASSO\n");
	
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
    geraSubsets(mao, jogadaAnterior);
  }
  
  return 0;
}