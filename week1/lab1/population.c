#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    // TODO: Prompt for end size
    
    int pop_ini;
    
    do
    {
        pop_ini = get_int("Type a population greater than 9 to start: ");
        
    }
    while (pop_ini < 9);
    
    int pop_end;
    do
    {
        pop_end = get_int("Type the population to reach: ");
    }
    while (pop_end < pop_ini);
    
    // TODO: Calculate number of years until we reach threshold
    // We can use a do or a while
    int new_pop = pop_ini;
    int year = 0;
    do
    {
        //Calculate number of borns and deaths 
        //As integer to round
        int born = new_pop / 3;
        int dead = new_pop / 4;
    
        //Calculate te new number
        new_pop = new_pop + born - dead;
        year++;
        
    }
    while (new_pop < pop_end);  

    // TODO: Print number of years
    if (pop_ini == pop_end)
    {
        printf("Years: 0 \n");
    }
    else
    {
        printf("Years: %i \n", year);
    }
    
}
