#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>

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


// escrever função combinacoesIguais (usar funcoes do guiao01)
int combinacoesIguais(wchar_t cartas[][100], int linhas)
{
   
    int eConjunto = 0;
    for(int n = 0; n < linhas; n++)
    {   
        //vê se é um conjunto
        if(conjunto(cartas[n],wcslen(cartas[n]))) eConjunto = 1;
        else
        {
            eConjunto = 0;
            break;
        }

    }

    int eSequencia = 0;
    for(int n = 0; n < linhas; n++)
    {   
        //vê se é uma sequencia
        if(seq(cartas[n],wcslen(cartas[n]),1)) eSequencia = 1;
        else
        {
            eSequencia = 0;
            break;
        }

    }

    int eDuplaSequencia = 0;
    for(int n = 0; n < linhas; n++)
    {   
        //vê se é uma dupla sequencia
        if(seq(cartas[n],wcslen(cartas[n]),2)) eDuplaSequencia = 1;
        else
        {
            eDuplaSequencia = 0;
            break;
        }

    }
    if(eConjunto || eSequencia || eDuplaSequencia) return 1;
    else return 0;

}


// escrever função tamanhoIgual

int tamanhoIgual(wchar_t cartas[][100], int linhas)
{
    int atualTamanho = wcslen(cartas[0]);
    for(int i = 0; i < linhas; i++){
        if (atualTamanho != wcslen(cartas[i])) return 0;
    }

    return 1;
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