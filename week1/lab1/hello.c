//Script para CS50, lab 01

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Saludar a alguien
    string answer = get_string("What is yor name? ");
    printf("Hello, %s\n !",answer);
}