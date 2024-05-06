#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <stdarg.h>

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

// verifica se todas as sequências são do mesmo tipo (conjunto, sequência ou dupla sequência)
int combinacoesIguais(wchar_t cartas[][100], int linhas)
{
   
    int eConjunto = 0;
    // verifica se todas as sequências são do tipo conjunto
    for(int n = 0; n < linhas; n++)
    {
        if(conjunto(cartas[n],wcslen(cartas[n]))) eConjunto = 1;
        else
        {
            eConjunto = 0;
            break;
        }
    }

    int eSequencia = 0;
    // verifica se todas as sequências são do tipo sequência
    for(int n = 0; n < linhas; n++)
    {
        if(seq(cartas[n],wcslen(cartas[n]),1)) eSequencia = 1;
        else
        {
            eSequencia = 0;
            break;
        }
    }

    int eDuplaSequencia = 0;
    // verifica se todas as sequências são do tipo sequência dupla
    for(int n = 0; n < linhas; n++)
    {
        if(seq(cartas[n],wcslen(cartas[n])/2,2)) eDuplaSequencia = 1;
        else
        {
            eDuplaSequencia = 0;
            break;
        }
    }

    if(eConjunto || eSequencia || eDuplaSequencia) return 1;
    else return 0;

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