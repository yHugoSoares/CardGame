#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>

// char cardvalues[14] = {'A', '2', '3', '3', '4', '5', '6', '7', '8', '9', '10', 'V', 'D', 'R'};

// int highestCard(char *card1, char *card2)
// {

// }

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
        return 0;
    }

    return 0;
}

int main()
{
    int l;
    wchar_t cards[100];
    if (scanf("%d", &l) != 1) return 0;
    

    for (int i = 0; i < l; i++){
        
        if (fgets(cards, 100, stdin) == 0) return 0;
        
        if (conjunto(cards) == 1)
            printf("conjunto com %d cartas onde a carta mais alta é %lc\n", countCards(cards), highestCard(cards));
        else if (seq(cards) == 1)
            printf("sequência com %d cartas onde a carta mais alta é %lc\n", countCards(cards), highestCard(cards));
        else if (dseq(cards) == 1)
            printf("dupla sequência com %d cartas onde a carta mais alta é %lc\n", countCards(cards)/2, highestCard(cards));
        else
            printf("Nada!");

    }

    setlocale(LC_ALL, "");
    wchar_t cards[100] = {0x1F0B6, 0x1F0C7, 0x1F0D3, 0x1F0AA};
    printf("A maior carta é: %lc\n", highestCard(cards));

    return 0;
}
