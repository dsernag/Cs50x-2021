//Variables = (total <- dinero recibido
//                cents <- dinero rec en cents
//              remain <- cents inic - q or d or n or p
//            q <- cantidad de quarters
//          d <- c. de dimes
//        n <- c. de nickels
//      p <- c. de pennies

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float total;
    int cents;
    int remain;
    int q = 0;
    int d = 0;
    int n = 0;
    int p = 0;
    do
    {
        total = get_float("Change owed: ");
    }
    while(total <= 0);
    cents = round(total*100);
    remain = cents;
    
    while (remain >= 25)
    {
        q++;
        remain -= 25;
    }
    while (remain >= 10)
    {
        q++;
        remain -= 10;
    }
    while (remain >= 5)
    {
        q++;
        remain -= 5;
    }
    while (remain >= 1)
    {
        q++;
        remain -= 1;
    }
    printf("%d\n", q);
}