#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Numero maximo de candidatos
#define MAX 9

// Tipo de variable que almacenara los candidatos y sus votos
typedef struct
{
    string name;
    int votes;
}
candidate;

// Matriz con la cantidad maxima de candidatos
candidate candidates[MAX];

// Numero de candidadots
int candidate_count;

// Funciones
bool vote(string name); //verifica que el voto corresponda al candidato y lo suma
void print_winner(void); //encuentra quien mas votos tuvo y lo imprime

int main(int argc, string argv[])
{
    // Deben haber mas de dos argumentos en el shell
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Verificar que no sean mas de los nueve candidadtos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) //Se llena la lista de candidatos con 0 votos cada uno
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: "); // Numero de veces que se permitira votar

    // Loop sobre el numero de votaciones
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Verificar que el voto corresponda a los candidatos
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Imprime el ganador
    print_winner();
}



// Devuelve la verificacion y acumula los votos
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++) //Loop sobre cada candidato
    {
        if(strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
        
    }
    return false;
}
// Imprimir el ganador
void print_winner(void)
{
    int pos; //posicion en la matriz del ganador y de la cantidad de votos
    int maxim; //maximo de votos
    maxim = candidates[0].votes; //busqueda linear del mayor
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > maxim)
            maxim = candidates[i].votes;
        
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == maxim)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
