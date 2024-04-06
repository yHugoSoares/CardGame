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
        if (cards[i] % 14 == cards[0] % 14)
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int seq(wchar_t cards[])
{
    wchar_t firstCard = cards[0];
    for (int i = 0; cards[i] != '\0'; i++)
    {
        if (firstCard == cards[i] + 1)
        {
            firstCard++;
        }
        else return 0;
    }
    return 1;
}

int dseq(wchar_t cards[])
{
    wchar_t cardCompare = cards[0];
    for (int i = 0; cards[i] != '\0'; i++)
    {
        if (cardCompare != cards[i]) return 0;
        cardCompare++;
    }
    return 1;
}

int main()
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

    

    return 0;
}