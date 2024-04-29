#ifndef FUNCTIONS_H
#define FUNCTIONS_H

wchar_t maiorCarta(wchar_t cartas[], int numCartas); // encontra a maior carta

int conjunto(wchar_t cartas[], int numCartas); // verifica se é um conjunto

int checkConsecutivo(wchar_t cartas[], int numCartas, int mult2, wchar_t cartaAtual, int *indexConsecutivo);

int checkImagem(wchar_t cartas[], int numCartas, int mult2, wchar_t cartaAtual);

int seq(wchar_t cartas[], int numCartas, int mult2); // verifica se é uma sequência

int combinacoesIguais(wchar_t cartas[][100], int linhas); // verifica se todas as sequências são do mesmo tipo (conjunto, sequência ou dupla sequência)

void printCartas(wchar_t cartas[][100], int linhas, int numCartas); // funcao que da print das cartas

int tamanhoIgual(wchar_t cartas[][100], int linhas); // verifica se todas as sequência têm o mesmo número de cartas

int comparaCartas(wchar_t carta1, wchar_t carta2); // compara duas cartas (retorna 1 quando a primeira é maior)

void swap(wchar_t cartas[][100], int i, int j, int numCartas); // implementação do swap para troca de posição duas sequências

void bsort(wchar_t cartas[][100], int linhas, int numCartas); // implementação do bubble sort para ordenar as sequências

void isort(wchar_t cartas[], int numCartas); // implementação do insertion sort para ordenar as cartas de uma sequência

void ordena(wchar_t cartas[][100], int linhas, int numCartas); // ordena as sequências e as cartas das sequências por ordem crescente

#endif