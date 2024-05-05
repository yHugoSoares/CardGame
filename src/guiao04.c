#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "functions.h"

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

int jogadaValida(wchar_t jogadaAnteriores[100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
        // verifica se a jogada anterior é "PASSO" e se a jogada atual é uma combinação válida
        if  (jogadaAnteriores[0] == 'P' && combinacaoValida(jogadaAtual)) continue;
        // verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
        else if (jogadaSuperior(jogadaAtual, jogadaAnteriores)) break;
        // se nenhuma das anteriores se verificar a jogada não é válida
        else return 0;
    
    return 1;
}

void printArray(wchar_t arr[], int tamanho) 
{

  for (int i = 0; i < tamanho; i++) 
  {
    if ((i + 1) == tamanho && arr[i] != '\0') wprintf(L"%lc", arr[i]);
    else if (arr[i] != '\0') wprintf(L"%lc ", arr[i]);
  }
  wprintf(L"\n");
}

void swap2(wchar_t *a, wchar_t *b) 
{
  wchar_t temp = *a;
  *a = *b;
  *b = temp;
}

void permutate(wchar_t cartas[], int inicio, int tamanho, wchar_t jogadaAnterior[]) 
{
  if (inicio == tamanho - 1) 
  {
    if (jogadaValida(jogadaAnterior, 1, cartas))
    {
      printArray(cartas, tamanho);
      return;
    } 
  }
  else
  {
    for (int i = inicio; i < tamanho; i++) 
    {
      swap2(&cartas[inicio], &cartas[i]);
      permutate(cartas, inicio + 1, tamanho, jogadaAnterior);
      swap2(&cartas[inicio], &cartas[i]);
    }
  }
}

void generateSubsets(wchar_t cartas[], wchar_t subset[], int tamanho, int index, wchar_t jogadaAnterior[]) 
{
  if (index == tamanho) 
  {
    permutate(subset, 0, tamanho, jogadaAnterior);
    return;
  }
  subset[index] = 0;
  generateSubsets(cartas, subset, tamanho, index + 1, jogadaAnterior);
  subset[index] = cartas[index];
  generateSubsets(cartas, subset, tamanho, index + 1, jogadaAnterior);
}

int main() {
  setlocale(LC_CTYPE, "C.UTF-8");

  int numTestes = 0;
  wchar_t cartas[] = L"🂠", jogadaAnterior[] = L"🂠"; // 🃌     🃜🂬🂼

  assert(wscanf(L"%d", &numTestes) == 1);
  for (int i = 0; i < numTestes; i++)
  {
    assert(wscanf(L"%100ls", &jogadaAnterior) == 1);
    assert(wscanf(L"%100ls", &cartas) == 1);
    int tamanho = sizeof(cartas) / sizeof(cartas[0]);
  
    wchar_t subset[tamanho];

    wprintf(L"Teste %d\n", i+1);
    generateSubsets(cartas, subset, tamanho, 0, jogadaAnterior);
  }
  return 0;  
}


//int main()
//{
//    setlocale(LC_CTYPE, "C.UTF-8");
//    
//    int testes;
//    wchar_t jogadaAnterior[1000];
//    wchar_t maoCartas[1000];
//
//    // lê o número de testes que vão ser lidos
//    assert(wscanf(L"%d", &testes) == 1);
//
//    // itera para cada teste
//    for (int i = 0; i < testes; i++)
//    {
//        // lê e guarda a jogada anterior
//        assert(wscanf(L"%1000ls", jogadaAnterior) != 0);
//
//        // lê e guarda a mao do jogador 
//        assert(wscanf(L"%1000ls", maoCartas) != 0);
//    
// 
//    //  print do teste atual
//        wprintf(L"Teste %d\n", i+1);
//
//        calculaJogadasPossiveis(jogadaAnterior,maoCartas);
//    
//        wprintf(L"%d\n", i+1);
//    }
//    
//    return 0;
//}
//
  
