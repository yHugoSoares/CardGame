#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <guiao01.c>

// função ordena por ordem crescente as cartas numa linha (e adiciona um espaço entre as cartas?)
// função que ordena por ordem crescente as sequências dentro de um teste

// retorna um valor diferente consoante o tipo de combinação da linha
int combinacaoValida (wchar_t cartas[], int numCartas){
    int r;
    if (conjunto(cartas, numCartas) == 1) r = 1;
    else if (seq(cartas, numCartas, 1) == 1) r = 2;
    else if (seq(cartas, numCartas/2, 2) == 1) r = 3;

    return r;
}

void merge (int r[], int a[], int b[], int na, int nb){
    int i, j, k = 0;

    while (i < na && j < nb) {
        if (a[i] <= b[j]) {
            r[k] = a[i];
            i++;
        } else {
            r[k] = b[j];
            j++;
        }
        k++;
    }
    while (i < na) {
        r[k] = a[i];
        i++;
        k++;
    }
    while (j < nb) {
        r[k] = b[j];
        j++;
        k++;
    }
}

void copy (wchar_t s[], wchar_t aux[], int numCartas){
    for (int i = 0; i < numCartas; i++){
        s[i] = aux [i];
    }
}
void msort (wchar_t cartas[], int numCartas){
    if (numCartas < 2) return;
    int m = numCartas/2;
    wchar_t aux[numCartas];
    msort (cartas, m);
    msort (cartas+m, numCartas-m);
    merge(cartas, m, cartas+m, numCartas-m, aux);
    copy(aux, cartas, numCartas);
}

int main() 
{    
    setlocale(LC_CTYPE, "C.UTF-8");
    
    int testes;
    int linhas;

    if (wscanf(L"%d", &testes) != 1) return 1; // lê o número de testes que vão ser lidos

    for (int i = 0; i < testes; ++i){ // itera para cada teste

    if (wscanf(L"%d", &linhas) != 1) return 1; // lê o número de linhas que vão ser lidas
        
        int primeiro_comprimento;
        int tipo_de_combinacao; // guarda o tipo da primeira linha
        wchar_t carta_mais_alta; // carta mais alta da primeira linha

        for (int j = 0; j < linhas; ++j){ // itera para cada linha

        int numCartas;

        wchar_t cartas[100]; // assume-se que cada conjunto de cartas tem no máximo 100 elementos

        if (wscanf(L"%100ls", cartas) == 0) return 1; // lê um conjunto de cartas

        numCartas = wcslen (cartas);

        if (j == 0)
        {
            primeiro_comprimento = numCartas;
            tipo_de_combinacao = combinacaoValida (cartas, numCartas);
            carta_mais_alta = maiorCarta(cartas, numCartas);
        }
        else if ((primeiro_comprimento != numCartas) || (tipo_de_combinacao != combinacaoValida (cartas, numCartas)))
        {
            printf ("Combinações não iguais!");
            break;
        }
        msort (cartas, numCartas);
        if (maiorCarta (cartas, numCartas) > carta_mais_alta){
            
        }
        }
    }
    return 0;
}
