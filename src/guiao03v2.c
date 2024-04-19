#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>

// KING VALUE (mod 16) == 14


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

// verifica se uma carta está presente na mão do jogador
int pertenceMao(wchar_t jogadaAtual[], wchar_t maoCartas[])
{
    long unsigned int r = 0;
    for(int j = 0; jogadaAtual[j] != 0; j++)
        for (int i = 0; maoCartas[i] != '\0'; i++)
            r += comparaCartas(jogadaAtual[j], maoCartas[i]);

    return (r == wcslen(jogadaAtual));
}

void retirarJogada(wchar_t jogadaAtual[], wchar_t maoCartas[])
{
    wchar_t temp[wcslen(maoCartas)];
    int k = 0;
    for(long unsigned int i = 0; i < wcslen(maoCartas); i++)
    {
        for (long unsigned int j = 0; j < wcslen(jogadaAtual); j++)
        {
            int naoEJogado = 1;
            if (maoCartas[j] == jogadaAtual[i]) naoEJogado = 0;
            if (naoEJogado)
            {
                temp[k++] = maoCartas[j];            
            }
        }
    }
    for(long unsigned int i = 0; i < wcslen(maoCartas); i++) maoCartas[i] = temp[i];
}

// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
int jogadaSuperior(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    int tipoIgual = 0;
    int tamanhoIgual = 0;
    int valorSuperior = 0;

    if ( (conjunto(jogadaAtual, wcslen(jogadaAtual)) && conjunto(jogadaAnterior, wcslen(jogadaAtual))) ||
         (seq(jogadaAtual, wcslen(jogadaAtual), 1)   && seq(jogadaAnterior, wcslen(jogadaAtual), 1))   ||
         (seq(jogadaAtual, wcslen(jogadaAtual)/2, 2) && seq(jogadaAnterior, wcslen(jogadaAtual)/2, 2))    )
            tipoIgual = 1;

    if (wcslen(jogadaAtual) == wcslen(jogadaAnterior))
            tamanhoIgual = 1;

    if (comparaCartas(maiorCarta(jogadaAtual, wcslen(jogadaAtual)), maiorCarta(jogadaAnterior, wcslen(jogadaAnterior))))
            valorSuperior = 1;

    if (tipoIgual && tamanhoIgual && valorSuperior) return 1;
    else return 0;
}


// combinacaoValida que testa se a jogada recebida como argumento é conjunto, seq ou dupla seq
int combinacaoValida(wchar_t jogadaAtual[])
{
    // Verifica se é um conjunto
    if (conjunto(jogadaAtual, wcslen(jogadaAtual)))
        return 0;
    // Verifica se é uma sequência
    if (seq(jogadaAtual, wcslen(jogadaAtual), 1))
        return 0;
    // Verifica se é uma dupla sequência
    if (seq(jogadaAtual, wcslen(jogadaAtual) / 2, 2))
        return 0;

    return 1;
}


int jogadaValida(wchar_t jogadasAnteriores[][100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
        // verifica se a jogada anterior é "PASSO" e se a jogada atual é uma combinação válida
        if  (jogadasAnteriores[i][0] == 'P' && combinacaoValida(jogadaAtual)) continue;
        // verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
        else if (jogadaSuperior(jogadaAtual, jogadasAnteriores[i])) break;
        // se nenhuma das anteriores se verificar a jogada não é válida
        else return 0;
    
    return 1;
}

void teste(wchar_t maoCartas[], wchar_t jogadasAnteriores[][100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
    // Verifica se as cartas jogadas pertencem à mão do jogador e são uma jogada válida
    if (pertenceMao(jogadaAtual, maoCartas) && jogadaValida(jogadasAnteriores, numJogadasAnteriores, jogadaAtual))
    {
        isort(maoCartas, wcslen(maoCartas));
        retirarJogada(maoCartas, jogadaAtual);
    }
}

void escrevecarta(wchar_t maoCartas[], int numCartas) // escreve as cartas com espacos entre elas
{
    for (int i = 0; i < numCartas; i++)
    {
        wprintf(L"%lc ", maoCartas[i]);
    }
    wprintf(L"\n");
}


int main()
{
    setlocale(LC_CTYPE, "C.UTF-8");
    
    int testes, numJogadasAnteriores;
    wchar_t jogadaAtual[100];
    wchar_t maoCartas[100];

    // lê o número de testes que vão ser lidos
    assert(wscanf(L"%d", &testes) == 1); 

    // itera para cada teste
    for (int i = 0; i < testes; i++)
    {
        // lê e guarda o número de jogadas passadas que vão ser lidas
        assert(wscanf(L"%d", &numJogadasAnteriores) == 1);

        // array de jogadas passadas
        wchar_t jogadasAnteriores[numJogadasAnteriores][100];

        // lê e guarda as cartas do jogador
        assert(wscanf(L"%100ls", maoCartas) != 0);
        
        // lê e guarda as jogadas anteriores (linha a linha)
        for (int j = 0; j < numJogadasAnteriores; j++)
            assert(wscanf(L"%100ls", &jogadasAnteriores[j][0]) != 0);
        
        // lê e guarda a jogada atual do jogador
        assert(wscanf(L"%100ls", jogadaAtual) != 0);

        // print do teste atual
        wprintf(L"Teste %d\n", i+1);

        // loop que imprime a mao com espaços
        teste(maoCartas, jogadasAnteriores, numJogadasAnteriores, jogadaAtual);
        escrevecarta(maoCartas, wcslen(maoCartas));
        //proximo teste
        retirarJogada(maoCartas, jogadaAtual);
        escrevecarta(maoCartas, wcslen(maoCartas));
        
    }
    
    return 0;
}
