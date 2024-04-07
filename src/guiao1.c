#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>

wchar_t maiorCarta(wchar_t cartas[], int numCartas) {

    wchar_t atualMaiorCarta = cartas[0];
    
    for (int i = 1; i < numCartas ; i++) { // encontra a maior carta
        if (cartas[i]%16 > atualMaiorCarta%16) // se a carta for maior
            atualMaiorCarta = cartas[i];
        else if (cartas[i]%16 == atualMaiorCarta%16 && cartas[i] > atualMaiorCarta) // se carta for igual e naipe maior
            atualMaiorCarta = cartas[i];
    }

    return atualMaiorCarta;
}

int conjunto(wchar_t cartas[], int numCartas)
{
    for (int i = 0; i < numCartas; i++)
        if (cartas[0]%16 != cartas[i]%16) return 0;

    return 1;
}

// 🃈🃙🂩🂧🃗🂨
// 🂸🃈🂧🃆🂷🂦

int seq(wchar_t cartas[], int numCartas){
    if (numCartas <= 2) return 0;

    wchar_t menorCarta = cartas[0];

    for (int i = 0; i < numCartas; i++) // encontra a menor carta
        if (cartas[i]%16 < menorCarta%16) menorCarta = cartas[i];
    
    wchar_t cartaAtual = menorCarta;

    for (int i = 0; i < numCartas-1;i++){ // itera as cartas em ordem crescente
        int temConsecutivo = 0;

        for (int j = 0; j < numCartas*2; j++){ // verifica se tem consecutivo
            if ((cartaAtual%16)+1 == cartas[j]%16){
                temConsecutivo = 1;
                cartaAtual = cartas[j];
                break;
            }
        }

        if (temConsecutivo == 0) return 0; // não é uma sequência
    }

    return 1; // é uma sequência
}

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int linhas;
    if (wscanf(L"%d", &linhas) != 1) return 1; // Lê o número de linhas que vão ser lidas

    for (int i = 0; i < linhas; ++i) { // Itera para cada linha

        wchar_t cartas[100]; // Assume-se que cada conjunto de cartas tem no máximo 100 elementos
        if (wscanf(L"%100ls", cartas) == 0) return 1; // Lê um conjunto de cartas

        int numCartas = wcslen(cartas);

        if (conjunto(cartas, numCartas) == 1)
            wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n",
                    numCartas, maiorCarta(cartas, numCartas));
        else if (seq(cartas, numCartas) == 1)
            wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n",
                    numCartas, maiorCarta(cartas, numCartas));
        else if (seq(cartas, numCartas/2) == 1)
            wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n",
                    numCartas/2, maiorCarta(cartas, numCartas));
        else wprintf(L"Nada!\n");

    }

    return 0;
}
