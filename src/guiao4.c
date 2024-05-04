#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>

wchar_t maiorCarta(wchar_t cartas[], int numCartas) // encontra a maior carta
{
    wchar_t atualMaiorCarta = cartas[0];

    // ordem dos naipes: espadas < copas < ouros < paus

    for (int i = 1; i < numCartas ; i++) // itera o conjunto de cartas
    {
        if (cartas[i]%16 > atualMaiorCarta%16) 
        // se a carta for maior
            atualMaiorCarta = cartas[i];
        else if (cartas[i]%16 == atualMaiorCarta%16 && cartas[i] > atualMaiorCarta) 
        // se carta for igual e naipe maior
            atualMaiorCarta = cartas[i];
    }

    return atualMaiorCarta;
}

int conjunto(wchar_t cartas[], int numCartas) // verifica se é um conjunto
{
    for (int i = 0; i < numCartas; i++)
    {
        if (cartas[0]%16 != cartas[i]%16) return 0; // se as cartas forem diferentes
        for (int j = 0; j < numCartas; j++)
        {
            if (cartas[i] == cartas[j] && i != j) return 0; // se houver cartas iguais
        }
    }    
    return 1;
}

int checkConsecutivo(wchar_t cartas[], int numCartas, int mult2, wchar_t cartaAtual, int *indexConsecutivo)
{
    for (int j = 0; j < numCartas*mult2; j++)
    {
        if ((cartaAtual%16)+1 == cartas[j]%16) // verifica se tem consecutivo
        {
            *indexConsecutivo = j;
            return 1;
        }
    }

    return 0;
}

int checkImagem(wchar_t cartas[], int numCartas, int mult2, wchar_t cartaAtual)
{
    for (int j = 0; j < numCartas*mult2; j++)
    {
        if (cartaAtual%16 == cartas[j]%16 && cartaAtual != cartas[j]) // verifica se tem imagem
        {
            return 1;
        }
    }

    return 0;
}

int seq(wchar_t cartas[], int numCartas, int mult2) // verifica se é uma sequência
{

    if (numCartas <= 2) return 0; // se não tem cartas suficientes para formar uma sequência

    wchar_t menorCarta = cartas[0];

    for (int i = 0; i < numCartas*mult2; i++) // encontra a menor carta
        if (cartas[i]%16 < menorCarta%16) menorCarta = cartas[i];
    
    wchar_t cartaAtual = menorCarta;

    for (int i = 0; i < numCartas;i++) // itera o conjunto de cartas por ordem crescente
    {
        int indexConsecutivo = 0;
        int temConsecutivo = 0;
        int temImagem = 1;

        if (i == numCartas-1) temConsecutivo = 1; // a última carta tem consecutivo por defeito
        else temConsecutivo = checkConsecutivo(cartas,numCartas,mult2,cartaAtual,&indexConsecutivo); // teste se tem consecutivo

        if (mult2 == 2) temImagem = checkImagem(cartas,numCartas,mult2,cartaAtual); // testa se tem imagem (caso dupla sequencia)

        if (temConsecutivo && temImagem) cartaAtual = cartas[indexConsecutivo];
        if (temConsecutivo == 0 || temImagem == 0) return 0; // se não tiver uma carta consecutiva ou imagem
    }

    return 1;
}

void printCartas(wchar_t cartas[][100], int linhas, int numCartas) // funcao que da print das cartas
{
    for (int k = 0; k < linhas; k++)
    {
       for (int t = 0; t < numCartas; t++)
       {
            if (t == numCartas-1)
                wprintf(L"%lc", cartas[k][t]);
            else
                wprintf(L"%lc ", cartas[k][t]);
       }
       wprintf(L"\n");
    }
}

int tamanhoIgual(wchar_t cartas[][100], int linhas) // verifica se todas as sequência têm o mesmo número de cartas
{
    int atualTamanho = wcslen(cartas[0]);
    for(int i = 0; i < linhas; i++){
        int tempTamanho = wcslen(cartas[i]);
        if (atualTamanho != tempTamanho) return 0;
    }

    return 1;
}

int comparaCartas(wchar_t carta1, wchar_t carta2) // compara duas cartas (retorna 1 quando a primeira é maior)
{
    if (carta1%16 > carta2%16 || (carta1%16 == carta2%16 && carta1 > carta2))
        return 1;
    else
        return 0;
}

void swap(wchar_t cartas[][100], int i, int j, int numCartas) // implementação do swap para troca de posição duas sequências
{
    wchar_t aux[numCartas];

    for(int k = 0; k < numCartas; k++)
        aux[k] = cartas[i][k];
    for(int k = 0; k < numCartas; k++)
        cartas[i][k] = cartas[j][k];
    for(int k = 0; k < numCartas; k++)
        cartas[j][k] = aux[k];
}

void bsort(wchar_t cartas[][100], int linhas, int numCartas) // implementação do bubble sort para ordenar as sequências
{	
    int i, j;	
    for (i = linhas; i > 0; i--)	
        for (j = 1; j < i; j++)	
            if (comparaCartas(cartas[j-1][numCartas-1],cartas[j][numCartas-1]))
                swap(cartas, j-1, j, numCartas);	
}

void isort(wchar_t cartas[], int numCartas) // implementação do insertion sort para ordenar as cartas de uma sequência
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

void ordena(wchar_t cartas[][100], int linhas, int numCartas) // ordena as sequências e as cartas das sequências por ordem crescente
{
    for (int i = 0; i < linhas; i++)
         isort(cartas[i], numCartas);
    bsort(cartas, linhas, numCartas);
}


int fatorial(int n)  
{
   int i, fat ;

   if (n <= 1)      
      return (1) ;

   fat = 1 ;
   for (i=2; i <= n; i++)
      fat *= i ;

   return (fat) ;
}


void troca_char(wchar_t *str, int p1, int p2)
{
  wchar_t tmp;
  tmp = str[p1]; 
  str[p1] = str[p2]; 
  str[p2] = tmp;
}

void permutacao_recursiva(wchar_t *str, int k)
{
  int i, len;
  len = wcslen(str);

  if (k == len) 
    wprintf(L"%ls\n", str);
  else 
  {
    for (i = k; i < len; i++) 
    {
      troca_char(str, k, i);
      permutacao_recursiva(str, k + 1);
      troca_char(str, i, k);
    }
  }
}

void lista_permutacoes(wchar_t *str)
{
  permutacao_recursiva(str, 0);
}



    //funcao que ve todas as jogadas que podem ser feitas com a mao do jogador 
int calculaJogadasPossiveis(jogadaAnterior,maoCartas){

    int combinacoesPossiveis = fatorial(wcslen(maoCartas));
    wchar_t CombinacoesPossiveis[combinacoesPossiveis][100];

    
}

void printArray(wchar_t arr[], int tamanho) {
    wprintf(L"{");
    for (int i = 0; i < tamanho; i++) {
        wprintf(L"%lc ", arr[i]);
    }
    wprintf(L"}\n");
}

void swap2(wchar_t *a, wchar_t *b) {
    wchar_t temp = *a;
    *a = *b;
    *b = temp;
}

void permutate(wchar_t cartas[], int inicio, int tamanho) {
    if (inicio == tamanho - 1) {
        printArray(cartas, tamanho);
        return;
    }
    
    for (int i = inicio; i < tamanho; i++) {
        swap2(&cartas[inicio], &cartas[i]);
        permutate(cartas, inicio + 1, tamanho);
        swap2(&cartas[inicio], &cartas[i]);
    }
}

void generateSubsets(wchar_t cartas[], wchar_t subset[], int tamanho, int index) {
    if (index == tamanho) {
        permutate(subset, 0, tamanho);
        return;
    }
    subset[index] = 0;
    generateSubsets(cartas, subset, tamanho, index + 1);
    subset[index] = cartas[index];
    generateSubsets(cartas, subset, tamanho, index + 1);
}

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    wchar_t cartas[] = { L'🂼', L'🂢', L'🃊' };
    int tamanho = sizeof(cartas) / sizeof(cartas[0]);
    wchar_t subset[tamanho];
    generateSubsets(cartas, subset, tamanho, 0);
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
  
