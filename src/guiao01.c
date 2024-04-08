#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>

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


int main() 
{    
    setlocale(LC_CTYPE, "C.UTF-8");
    
    int linhas;
    if (wscanf(L"%d", &linhas) != 1) return 1; // lê o número de linhas que vão ser lidas

    for (int i = 0; i < linhas; ++i) // itera para cada linha
    {

        wchar_t cartas[100]; // assume-se que cada conjunto de cartas tem no máximo 100 elementos
        if (wscanf(L"%100ls", cartas) == 0) return 1; // lê um conjunto de cartas

        int numCartas = wcslen(cartas);

        if (conjunto(cartas, numCartas) == 1)
            wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n",
                    numCartas, maiorCarta(cartas, numCartas));
        else if (seq(cartas, numCartas, 1) == 1)
            wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n",
                    numCartas, maiorCarta(cartas, numCartas));
        else if (seq(cartas, numCartas/2, 2) == 1)
            wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n",
                    numCartas/2, maiorCarta(cartas, numCartas));
        else wprintf(L"Nada!\n");

    }

    return 0;
}
