//Computates de Coleman-Liau Index

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string t);
int count_words(string t);
int count_sentences(string t);
int coleman_liau(int l, int w, int s);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text); //count the number of letters
    int words = count_words(text); //count the number of words
    int sentences = count_sentences(text); //count the number of sentences
    int coleman = coleman_liau(letters, words, sentences); //calculates the Coleman-Liau index
    if (coleman <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman >= 1 && coleman < 16)
    {
        printf("Grade %i\n", coleman);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

//Function to count letters:

int count_letters(string t)
{
    int count = 0;
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (t[i] >= 'a' && t[i] <= 'z')
        {
            count++;
        }
        else if (t[i] >= 'A' && t[i] <= 'Z')
        {
            count++;
        }
    }
    return (count);
}

//Fuction to count words

int count_words(string t)
{
    int count = 1;
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (t[i] == ' ')
        {
            count++;
        }
    }
    return (count);
}

//Function to count sentences

int count_sentences(string t)
{
    int count = 0;
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            count++;
        }
    }
    return (count);
}

//Function to calculate Coleman-Liau Index

int coleman_liau(int l, int w, int s)
{
    int coleman;
    float L = (l * 100) / w;
    float S = (s * 100) / w;
    coleman = round(0.0588 * L - 0.296 * S - 15.8);
    return (coleman);
}
