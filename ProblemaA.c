#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
wchar_t highestCard(wchar_t cards[])
{
    wchar_t cardCompare  = cards[0];
    for (int i = 0; cards[i] != '\0' ; i++)
    {
        if (cardCompare < cards[i]) cardCompare = cards[i];
    }   
    return cardCompare;
}


int countCards(wchar_t cards[])
{
    int count = 0;
    for (int i = 0; cards[i] != '\0'; i++)
    {
        count++;
    }
    return count;
}


int conjunto(wchar_t cards[])
{
    for (int i = 0; cards[i] != '\0'; i++)
    {
        if (cards[i] % 14 != cards[0] % 14)
        {
            return 0; // as cartas nao tem o mesmo valor
        }
    }
    return 1; // todas tem o mesmo valor 
}


int seq(wchar_t cards[])
{
    int numCartas = countCards(cards);
    for (int i = 0; i < numCartas - 1; i++) {
        wchar_t cartaAtual = cards[i];
        int  aux = 0;
        for (int j = 0; j < numCartas; j++) {
            if (cards[j] == cartaAtual) {
                aux ++;
            }
        }
        if (!aux) return 0; // Não encontrou a próxima carta na sequência
    }
    return 1; // Todas as cartas estão em ordem na sequência
}
int dseq(wchar_t cards[])
{
    wchar_t cardCompare = cards[0];
    for (int i = 1; cards[i] != '\0'; i++)
    {
        if (cardCompare != cards[i]) return 0; // nao tem o mesmo valor 
        cardCompare = cards[i];
        i++;
    }
    return 1; // formam dupla sequencia 
}
/*int main()
{
    setlocale(LC_ALL, "");
    int l;
    wchar_t cards[100] = {0x1F0BA, 0x1F0CA, 0x1F0DA, 0x1F0AA};
    if (scanf("%d\n", &l) != 1) return 0;
    for (int i = 0; i < l; i++)
    {
        if (wscanf(L"%100ls", cards) == 0) return 0;
        if (conjunto(cards) == 1)
            wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n", countCards(cards), highestCard(cards));
        else if (dseq(cards) == 1)
            wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n", countCards(cards), highestCard(cards));
        else if (seq(cards) == 1)
            wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n", countCards(cards)/2, highestCard(cards));
        else
            printf("Nada!\n");
    }
}

*/
int main() {
    setlocale(LC_ALL, "");
    int linhas;
    if (wscanf(L"%d", &linhas) != 1) return 1; // Lê o número de linhas que vão ser lidas
    for (int i = 0; i < linhas; ++i) { // Itera para cada linha
        wchar_t cartas[100]; // Assume-se que cada conjunto de cartas tem no máximo 100 elementos
        if (wscanf(L"%99ls", cartas) == 0) return 1; // Lê um conjunto de cartas
    
        if (conjunto(cartas) == 1 && dseq (cartas) == 0 && seq (cartas) == 0){
            wprintf(L"\nconjunto com %ld cartas onde a carta mais alta é %lc\n", wcslen(cartas), highestCard(cartas));
        }
        if (seq (cartas) == 1 && dseq (cartas) == 0 && conjunto(cartas) == 0){
            wprintf(L"\nsequencia com %ld cartas onde a carta mais alta é %lc\n", wcslen(cartas), highestCard(cartas));
        }
        if (dseq (cartas) == 1 && seq (cartas) == 0 && conjunto(cartas) == 0){
            wprintf(L"\ndupla sequencia com %ld cartas onde a carta mais alta é %lc\n", wcslen(cartas), highestCard(cartas));
        }
        if (dseq (cartas) == 0 && seq (cartas) == 0 && conjunto(cartas) == 0)
            wprintf(L"\nNada em %ls !\n", cartas);
    }
    return 0;
}

