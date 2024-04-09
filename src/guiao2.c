#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>


// escrever função combinacoesIguais (usar funcoes do guiao01)


// escrever função tamanhoIgual


// escrever função ordena



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
        // lê o número de linhas que vão ser lidas
        if (wscanf(L"%d", &linhas) != 1) return 1;

        // array de sequência de cartas
        wchar_t cartas[linhas][100];

        // itera para cada linha
        for (int j = 0; j < linhas; j++)
            // guarda as linhas num array (array de sequência de cartas)
            if (wscanf(L"%100ls", &cartas[j][0]) == 0) return 1;

        // print do teste atual        
        wprintf(L"Teste %d\n", i+1);

        // verifica se as sequências de cartas são do mesmo tipo e tamanho
        if (combinacoesIguais(cartas) && tamanhoIgual(cartas)){
            
            // ordena as cartas por ordem crescente
            ordena(cartas);

            // print das sequências de cartas ordenadas
            for (int k = 0; k < linhas; k++)
                wprintf(L"%ls\n", cartas[k]);

        }
        // caso não tenham o mesmo tipo ou tamanho
        else wprintf(L"Combinações não iguais!");


    }
    
    return 0;
}

// função ordena por ordem crescente as cartas numa linha (e adiciona um espaço entre as cartas?)
// função que ordena por ordem crescente as sequências dentro de um teste

// retorna um valor diferente consoante o tipo de combinação da linha
// int combinacaoValida (wchar_t cartas[], int numCartas){
    // int r;
    // if (conjunto(cartas, numCartas) == 1) r = 1;
    // else if (seq(cartas, numCartas, 1) == 1) r = 2;
    // else if (seq(cartas, numCartas/2, 2) == 1) r = 3;
// 
    // return r;
// }
// 
// void merge (int r[], int a[], int b[], int na, int nb){
    // int i, j, k = 0;
// 
    // while (i < na && j < nb) {
        // if (a[i] <= b[j]) {
            // r[k] = a[i];
            // i++;
        // } else {
            // r[k] = b[j];
            // j++;
        // }
        // k++;
    // }
    // while (i < na) {
        // r[k] = a[i];
        // i++;
        // k++;
    // }
    // while (j < nb) {
        // r[k] = b[j];
        // j++;
        // k++;
    // }
// }
// 
// void copy (wchar_t s[], wchar_t aux[], int numCartas){
    // for (int i = 0; i < numCartas; i++){
        // s[i] = aux [i];
    // }
// }
// void msort (wchar_t cartas[], int numCartas){
    // if (numCartas < 2) return;
    // int m = numCartas/2;
    // wchar_t aux[numCartas];
    // msort (cartas, m);
    // msort (cartas+m, numCartas-m);
    // merge(cartas, m, cartas+m, numCartas-m, aux);
    // copy(aux, cartas, numCartas);
// }

        // int primeiro_comprimento;
        // int tipo_de_combinacao; // guarda o tipo da primeira linha
        // wchar_t carta_mais_alta; // carta mais alta da primeira linha
// 
        // for (int j = 0; j < linhas; ++j) // itera para cada linha
        // {
// 
            // wchar_t cartas[100]; // assume-se que cada conjunto de cartas tem no máximo 100 elementos
            // if (wscanf(L"%100ls", cartas) == 0) return 1; // lê um conjunto de cartas
// 
            // int numCartas = wcslen (cartas);
// 
            // if (j == 0)
            // {
                // primeiro_comprimento = numCartas;
                // tipo_de_combinacao = combinacaoValida (cartas, numCartas);
                // carta_mais_alta = maiorCarta(cartas, numCartas);
            // }
            // else if ((primeiro_comprimento != numCartas) ||
                    //  (tipo_de_combinacao != combinacaoValida (cartas, numCartas)))
            // {
                // printf ("Combinações não iguais!");
                // break;
            // }
            // msort (cartas, numCartas);
            // if (maiorCarta (cartas, numCartas) > carta_mais_alta){
            // }
// 
        // }
