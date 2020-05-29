//Double mario columns

#include <stdio.h>
#include <cs50.h>

void print(char c, int h);

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
        print(' ', h - 1 - i);
        print('#', i + 1);
        print(' ', 2);
        print('#', i + 1);
        printf("\n");
    }
    
}

// Function to print some character i times

void print(char c, int h) //This function computes a line of print the spaces and dashes
{
    for (int i = 0; i < h; i++)
    {
        printf("%c", c);
    }
}
