#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>

// Código dos guiões passados

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

int comparaCartas(wchar_t carta1, wchar_t carta2) // compara duas cartas (retorna 1 quando a primeira é maior)
{
    if (carta1%16 > carta2%16 || (carta1%16 == carta2%16 && carta1 > carta2))
        return 1;
    else
        return 0;
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

// Novo Código

// verifica se as cartas da jogada atual estão presentes na mão do jogador
int pertenceMao(wchar_t jogadaAtual[], wchar_t maoCartas[])
{
    int tamanhoMao = wcslen(maoCartas);
    int tamanhoJogada = wcslen(jogadaAtual);
    int r = 0;
    for(int i = 0; i < tamanhoJogada; i++)
        for (int j = 0; j < tamanhoMao; j++)
            if (jogadaAtual[i] == maoCartas[j])
                r++;

    if (r == tamanhoJogada) return 1;
    else return 0;
}

// retira da mão do jogador as cartas presentes na jogada atual
void retirarJogada(wchar_t jogadaAtual[], wchar_t maoCartas[])
{
    int tamanhoMao = wcslen(maoCartas);
    int tamanhoJogada = wcslen(jogadaAtual);
    wchar_t temp[tamanhoMao];
    int tempIndex = 0;

    for(int i = 0; i < tamanhoMao; i++)
    {
        for (int j = 0; j < tamanhoJogada; j++)
        {
            if (maoCartas[i] != jogadaAtual[j])
            {
                temp[tempIndex] = maoCartas[i];
                tempIndex++;
            }
        }
        temp[tempIndex] = '\0';
    }
    wcscpy(maoCartas, temp);
}

int casosEspeciais(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    int tamanhoJogada = wcslen(jogadaAtual);
    int tamanhoAnterior = wcslen(jogadaAnterior);

    int tudoReis = 1;
    for (int i = 0; i < tamanhoAnterior; i++)
        if (jogadaAnterior[i] % 16 != 14) tudoReis = 0;
    
    if (tudoReis)
    {
        if (tamanhoAnterior == 1 && conjunto(jogadaAtual, tamanhoJogada) && tamanhoJogada == 4)
            return 1;
        else if (tamanhoAnterior == 1 && seq(jogadaAtual, tamanhoJogada/2, 2) && tamanhoJogada/2 == 3)
            return 1;
        else if (tamanhoAnterior == 2 && seq(jogadaAtual, tamanhoJogada/2, 2) && tamanhoJogada/2 == 4)
            return 1;
        else if (tamanhoAnterior == 3 && seq(jogadaAtual, tamanhoJogada/2, 2) && tamanhoJogada/2 == 5)
            return 1;
    }

    return 0;
}


// verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
int jogadaSuperior(wchar_t jogadaAtual[], wchar_t jogadaAnterior[])
{
    if (casosEspeciais(jogadaAtual, jogadaAnterior)) return 1;
    
    int tamanhoJogada = wcslen(jogadaAtual);
    int tamanhoAnterior = wcslen(jogadaAnterior);
    int tipoIgual = 0;
    int tamanhoIgual = 0;
    int valorSuperior = 0;

    if (conjunto(jogadaAtual,tamanhoJogada) && conjunto(jogadaAnterior, tamanhoAnterior))
        tipoIgual = 1;
    else if (seq(jogadaAtual, tamanhoJogada, 1) && seq(jogadaAnterior, tamanhoAnterior, 1))
        tipoIgual = 1;
    else if (seq(jogadaAtual, tamanhoJogada/2, 2) && seq(jogadaAnterior, tamanhoAnterior/2, 2))
        tipoIgual = 1;

    if (wcslen(jogadaAtual) == wcslen(jogadaAnterior))
            tamanhoIgual = 1;

    if (comparaCartas(maiorCarta(jogadaAtual, wcslen(jogadaAtual)), maiorCarta(jogadaAnterior, wcslen(jogadaAnterior))))
            valorSuperior = 1;

    if (tipoIgual && tamanhoIgual && valorSuperior) return 1;
    else return 0;
}

// escrever combinacaoValida que testa se a jogada recebida como argumento é conjunto, seq ou dupla seq
int combinacaoValida(wchar_t jogadaAtual[])
{
    int tamanhoJogada = wcslen(jogadaAtual);
    if  ((conjunto(jogadaAtual, tamanhoJogada)) ||
         (seq(jogadaAtual, tamanhoJogada, 1))   ||
         (seq(jogadaAtual, tamanhoJogada/2, 2))   )
            return 1;
    else return 0;
}

// verifica se a jogada é válida
int jogadaValida(wchar_t jogadasAnteriores[][100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
    if (numJogadasAnteriores == 0)
        return combinacaoValida(jogadaAtual);

    for (int i = numJogadasAnteriores-1; i > numJogadasAnteriores-4 && i > 0; i--)
    {
        // verifica se a jogada anterior é "PASSO" e se a jogada atual é uma combinação válida
        if  (jogadasAnteriores[i][0] == 'P' && combinacaoValida(jogadaAtual))
            continue;
        // verifica se a jogada atual é do mesmo tipo, de tamanho igual e de valor superior à jogada anterior
        else if (jogadaSuperior(jogadaAtual, jogadasAnteriores[i]))
            break;
        // se nenhuma das anteriores se verificar a jogada não é válida
        else return 0;
    }
    
    return 1;
}

// verifica se a jogada é válida e modifica a mão do jogador
int aplicaJogada(wchar_t maoCartas[], wchar_t jogadasAnteriores[][100], int numJogadasAnteriores, wchar_t jogadaAtual[])
{
    // verifica se as cartas jogadas pertencem à mão do jogador e são uma jogada válida
    if (pertenceMao(jogadaAtual, maoCartas) && jogadaValida(jogadasAnteriores, numJogadasAnteriores, jogadaAtual))
    {
        retirarJogada(jogadaAtual, maoCartas);
        return 1;
    }
    
    return 0;
}


void imprimeMao(wchar_t maoCartas[], int tamanhoMao)
{
    if (tamanhoMao == 0) wprintf(L"\n");
    else 
        for(int i = 0; i < tamanhoMao; i++)
        {
            if (i == tamanhoMao - 1)
                wprintf(L"%lc\n", maoCartas[i]);
            else wprintf(L"%lc ", maoCartas[i]);
        }
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

        // verifica se a jogada é válida e modifica a mão do jogador
        int jogadaAplicada = aplicaJogada(maoCartas, jogadasAnteriores, numJogadasAnteriores, jogadaAtual);
        
        // determina o número de cartas na mão do jogador depois da jogada
        int tamanhoMao = wcslen(maoCartas);
        if (jogadaAplicada) tamanhoMao -= wcslen(jogadaAtual);

        // ordena as cartas
        isort(maoCartas, tamanhoMao);

        // imprime a mão do jogador
        imprimeMao(maoCartas, tamanhoMao);
        
    }
    
    return 0;
}