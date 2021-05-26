// Creating pyramidal colum # characters
// It takes H as height, and recreates a pyramid block like Mario videogame

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);
    for (int i = 0; i < h; i++)
    {
        for (int n = 0; n < h - 1 - i; n++) //to generate spaces
        {
            printf(" ");    
        }
        for (int j = 0; j < i + 1 ; j++) //to invert the hashes direction
        {
            printf("#"); 
        }
        printf("\n");       
    }
}