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
        int tempTamanho = wcslen(cartas[i]);
        if (atualTamanho != tempTamanho) return 0;
    }

    return 1;
}

// funcao insertion sort
void isort(wchar_t a[], int numCartas) 
{	
    int i, j;
    wchar_t aux;
    for (i = 0; i < numCartas; i++) 
    {
        aux = a[i];	
        for (j = i; j > 0 && a[j-1] > aux; j--) a[j] = a[j-1];	
        a[j] = aux;	
    }	
}

void swap (int v[][100], int i, int j, int numCartas){
    
    wchar_t aux[numCartas];

    for(int k = 0; k < numCartas; k++){
        aux[k] = v[i][k];
    }
    for(int k = 0; k < numCartas; k++){
        v[i][k] = v[j][k];
    }
    for(int k = 0; k < numCartas; k++){
        v[j][k] = aux[k];
    }
}

// funcao bubble sort
void bsort(int cartas[][100], int linhas, int numCartas) {	
        int i, j;	
        for (i = linhas; i > 0; i--)	
            for (j = 1; j < i; j++)	
                if (cartas[j-1][numCartas] > cartas[j][numCartas])	
                    swap(cartas, j-1, j, numCartas);	
}

// escrever função ordena
void ordena(wchar_t cartas[][100], int linhas)
{
    int numCartas = wcslen(cartas[0]);
    for (int i = 0; i < linhas; i++)
    {
        isort(cartas[i], numCartas);
    }
    bsort(cartas, linhas, numCartas);
    // for (int i = 0; i < linhas; i++)
    // {
        // if (maiorCarta(cartas[i], numCartas) > maiorCarta(cartas[i+1], numCartas))
    // }
    
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
        wprintf(L"Tamanho igual:%d ; Combinacao igual:%d\n", tamanhoIgual(cartas,linhas), combinacoesIguais(cartas,linhas));
        if (tamanhoIgual(cartas, linhas) && combinacoesIguais(cartas, linhas)){
            
            // ordena as cartas por ordem crescente
            ordena(cartas, linhas);

            // print das sequências de cartas ordenadas
            for (int k = 0; k < linhas; k++)
                wprintf(L"%ls\n", cartas[k]);

        }
        // caso não tenham o mesmo tipo ou tamanho
        else wprintf(L"Combinações não iguais!\n");


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
 
