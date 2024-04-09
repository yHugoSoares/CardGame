#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>


// funcao que determina a maior carta
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

// verifica se é um conjunto
int conjunto(wchar_t cartas[], int numCartas)
{
    for (int i = 0; i < numCartas; i++)
    {
         // se as cartas forem diferentes
        if (cartas[0]%16 != cartas[i]%16) return 0;
        for (int j = 0; j < numCartas; j++)
            // se houver cartas iguais
            if (cartas[i] == cartas[j] && i != j) return 0;
    }    
    return 1;
}

// verifica se tem consecutivo
int checkConsecutivo(wchar_t cartas[], int numCartas, int mult2, wchar_t cartaAtual, int *indexConsecutivo)
{
    for (int j = 0; j < numCartas*mult2; j++)
        if ((cartaAtual%16)+1 == cartas[j]%16) 
        {
            *indexConsecutivo = j;
            return 1;
        }

    return 0;
}

// verifica se tem imagem
int checkImagem(wchar_t cartas[], int numCartas, int mult2, wchar_t cartaAtual)
{
    for (int j = 0; j < numCartas*mult2; j++)
        if (cartaAtual%16 == cartas[j]%16 && cartaAtual != cartas[j]) return 1;

    return 0;
}

// verifica se é uma sequência
int seq(wchar_t cartas[], int numCartas, int mult2)
{

    // se não tem cartas suficientes para formar uma sequência
    if (numCartas <= 2) return 0;

    wchar_t menorCarta = cartas[0];

    // encontra a menor carta
    for (int i = 0; i < numCartas*mult2; i++)
        if (cartas[i]%16 < menorCarta%16) menorCarta = cartas[i];
    
    wchar_t cartaAtual = menorCarta;

    // itera o conjunto de cartas por ordem crescente
    for (int i = 0; i < numCartas;i++)
    {
        int indexConsecutivo = 0;
        int temConsecutivo = 0;
        int temImagem = 1;

        // se for a última carta tem consecutivo por defeito, se não testa se tem consecutivo
        if (i == numCartas-1) temConsecutivo = 1;
        else temConsecutivo = checkConsecutivo(cartas,numCartas,mult2,cartaAtual,&indexConsecutivo);

        // testa se tem imagem (no caso de dupla sequência)
        if (mult2 == 2) temImagem = checkImagem(cartas,numCartas,mult2,cartaAtual);

        if (temConsecutivo && temImagem) cartaAtual = cartas[indexConsecutivo];

        // se não tiver uma carta consecutiva ou imagem
        if (temConsecutivo == 0 || temImagem == 0) return 0;
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

// verifica se todas as sequência têm o mesmo número de cartas
int tamanhoIgual(wchar_t cartas[][100], int linhas)
{
    int atualTamanho = wcslen(cartas[0]);
    for(int i = 0; i < linhas; i++){
        int tempTamanho = wcslen(cartas[i]);
        if (atualTamanho != tempTamanho) return 0;
    }

    return 1;
}

// implementação do swap para troca de posição duas sequências
void swapS (int cartas[][100], int i, int j, int numCartas){
    
    wchar_t aux[numCartas];

    for(int k = 0; k < numCartas; k++){
        aux[k] = cartas[i][k];
    }
    for(int k = 0; k < numCartas; k++){
        cartas[i][k] = cartas[j][k];
    }
    for(int k = 0; k < numCartas; k++){
        cartas[j][k] = aux[k];
    }
}

// implementação do bubble sort para ordenar as sequências
void bsortS(wchar_t cartas[][100], int linhas, int numCartas) {	
        int i, j;	
        for (i = linhas; i > 0; i--)	
            for (j = 1; j < i; j++)	
                if (cartas[j-1][numCartas-1]%16 > cartas[j][numCartas-1]%16 ||
                    (cartas[j-1][numCartas-1]%16 == cartas[j][numCartas-1]%16 &&
                     cartas[j-1][numCartas-1] > cartas[j][numCartas-1]))
                    swapS(cartas, j-1, j, numCartas);	
}

// implementação do swap para troca de posição duas cartas
void swapC (wchar_t cartas[], int i, int j){
    wchar_t aux = cartas[i];
    cartas[i] = cartas[j];
    cartas[j] = aux;
}

// implementação do bubble sort para ordenar as cartas de uma sequência
void bsortC(wchar_t cartas[], int numCartas) {	
        int i, j;	
        for (i = numCartas; i > 0; i--)	
            for (j = 1; j < i; j++)	
                if (cartas[j-1]%16 > cartas[j]%16 || (cartas[j-1]%16 == cartas[j]%16 && cartas[j-1] > cartas[j]))	
                    swapC(cartas, j-1, j);	
}


// ordena as sequências e as cartas das sequências por ordem crescente
void ordena(wchar_t cartas[][100], int linhas, int numCartas)
{
    for (int i = 0; i < linhas; i++)
        bsortC(cartas[i], numCartas);
        // isort(cartas[i], numCartas);
    bsortS(cartas, linhas, numCartas);
}

void printCartas(wchar_t cartas[][100], int linhas, int numCartas)
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

int main()
{    
    setlocale(LC_CTYPE, "C.UTF-8");
    
    int testes;
    int linhas;

    // lê o número de testes que vão ser lidos
    if (wscanf(L"%d", &testes) != 1) return 1; 

    // itera para cada teste
    for (int i = 0; i < testes; i++)
    {
        // lê e guarda o número de linhas que vão ser lidas
        if (wscanf(L"%d", &linhas) != 1) return 1;

        // array de sequência de cartas
        wchar_t cartas[linhas][100];

        // lê e guarda o input de cada linha num array (array de sequência de cartas)
        for (int j = 0; j < linhas; j++)
            if (wscanf(L"%100ls", &cartas[j][0]) == 0) return 1;
        
        // print do teste atual
        wprintf(L"Teste %d\n", i+1);

        // verifica se as sequências de cartas são do mesmo tipo e tamanho
        if (tamanhoIgual(cartas, linhas) && combinacoesIguais(cartas, linhas))
        { 
            // número de cartas em cada sequência
            int numCartas = wcslen(cartas[0]);

            // ordena as sequências e as cartas das sequências por ordem crescente
            ordena(cartas, linhas, numCartas);


            printCartas(cartas, linhas, numCartas);
            // print das sequências de cartas ordenadas

        }
        // caso não tenham o mesmo tipo ou tamanho
        else wprintf(L"Combinações não iguais!\n");

    }
    
    return 0;
}
