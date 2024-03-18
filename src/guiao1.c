#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <uchar.h>

// char cardvalues[14] = {'1', '2', '3', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E'};

wchar_t highestCard(wchar_t cards[])
{
    wchar_t cardCompare  = cards[0];
    for (int i = 0; cards[i] != '\0' ; i++)
    {
        if (cardCompare < cards[i])
        {
            cardCompare = cards[i];
        }
    }   
    return cardCompare;
}


int main()
{
    setlocale(LC_ALL, "");
    wchar_t cards[100] = {0x1F0B6, 0x1F0C7, 0x1F0D3, 0x1F0AA};
    printf("A maior carta é: %lc\n", highestCard(cards));

}