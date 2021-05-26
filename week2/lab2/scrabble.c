#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//Funcion declarada abajo
int compute_score(string word);

int main(void)
{

    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    ///////////Scores:

    //printf("Player1score: %i\n", score1);
    //printf("Player2score: %i\n", score2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{

    //Crear un alfabeto de ASCII mayusculas
    char alfabeto[26];
    
    for (int i = 0; i <= 25; i++)
    {
        alfabeto[i] = i + 65;
    }

    //Definir una variable que acumule los puntos:
    int puntos = 0;

    // Se deben correr dos for, uno sobre la palabra escrita y otro sobre el alfabeto

    //1er for sobre la palabra
    int longitud = strlen(word);

    for (int i = 0; i <= longitud; i++)
    {
        //Definir el caracter como mayuscula y pasarlo a ASCII
        char caracter = toupper(word[i]);
        int ASCII_char = caracter;

        for (int j = 0; j <= 25; j++)
        {
            if (ASCII_char == alfabeto[j])
            {
                puntos += POINTS[j];
            }
            else
            {
                puntos += 0;
            }
        }
    }
    return puntos;
}
