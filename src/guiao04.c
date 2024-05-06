#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <ctype.h>
#include "functions.h"

// void retiraEspacos(wchar_t arr[])
// {
//   int len = wcslen(arr), k = 0;
//   wchar_t temp[len];
//   for (int i = 0; i < len; i++)
//   {
//     if (arr[i] != L'0') temp[k++] = arr[i];
//   }
//   for (int i = 0; i < len; i++)
//   {
//     arr[i] = temp[i];
//   }
// }

// int emptyArray(wchar_t arr[], int tamanho)
// {
//   for (int i = 0; i < tamanho; i++)
//   {
//     if (arr[i] != '\0' || arr[i] != L' ') return 0;
//   }
//   return 1;
// }

// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
int jogadaSuperior(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
	int tipoIgual = 0;
	int tamanhoIgual = 0;
	int valorSuperior = 0;

	if ((conjunto(jogadaAtual, wcslen(jogadaAtual)) && conjunto(jogadaAnterior, wcslen(jogadaAtual)))   ||
		(seq(jogadaAtual, wcslen(jogadaAtual), 1)   && seq(jogadaAnterior, wcslen(jogadaAtual), 1)) 	||
		(seq(jogadaAtual, wcslen(jogadaAtual)/2, 2) && seq(jogadaAnterior, wcslen(jogadaAtual)/2, 2)))
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
	{
		r *= n;
	}
	return r;
}

// Function to generate all substrings of a given word
void generateSubstrings(const wchar_t *word, wchar_t jogadaAnterior[]) 
{
	int len = wcslen(word);
	int numSubstrings = power(2, len) - 1; // Calculate the number of substrings
	wchar_t cartasSubStrings[numSubstrings][100];
	
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

		if(jogadaValida(jogadaAnterior, substring)) cartasSubStrings[i-1][0] = substring;

		// Free allocated memory
		free(substring);
  	}
	ordena(cartasSubStrings, numSubstrings, wcslen(cartasSubStrings[0]));
	for (int i = 0; i < wcslen(cartasSubStrings); i++)
	{
		imprimeMao(cartasSubStrings[i], wcslen(cartasSubStrings[i]));
	}
	
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
    generateSubstrings(mao, jogadaAnterior);
  }
  
  return 0;
}