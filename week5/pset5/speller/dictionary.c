// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = ((LENGTH + 1) * 'z');

// Hash table
int total_words = 0;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Usar la función hash para obtener el valor ascii
    int index = hash(word);

    //Acceder a ese índice en la hash table
    //Variable temporal
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Iterar sobre cada palabra
    //Obtener la suma de los caracteres
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Abrir el diccionario:
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //Leer de a una palabra del archivo:
    //Definir el buffer del tamaño del buffer de las palabras:
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        //Crear un nodo del tamaño de la estructra:
        node *new_node = malloc(sizeof(node));
        //Verificar el nodo
        if (new_node == NULL)
        {
            return false;
        }

        //Copiar la palabra al nodo
        strcpy(new_node->word, word);
        new_node->next = NULL;

        //Obtener el índice de la palabra
        int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = new_node;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }

        total_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //Retornar el total de palabras
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Liberar la linked list
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor =  cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
