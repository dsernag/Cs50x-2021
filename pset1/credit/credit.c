//

#include <stdio.h>
#include <cs50.h>

//Funciones
bool validity();
int find_length(long long n);
bool checksum(long long ccn);
void print_type(long long ccn);
//

int main(void)
{
    long long number;
    do
    {
        number = get_long_long("Number: "); 
    } 
    while (number < 0);
    
    if (validity(number) == true) // Si la funcion validity arroja TRUE
    {
        print_type(number); //Ejecuta la funcion print_type
    }
    
    else
    {
        printf("INVALID\n");
    }
}

// funcion principal

bool validity(long long number) //Funcion para validar si es, o no tarjeta de credito 
{                       
    int lenght = find_length(number); //Funcion para encontrar la longitud
    return (lenght == 13 || lenght == 15 || lenght == 16) && checksum(number); 
    //Debe retornar un TRUE para continuar con el proceso anterior
}

//Dependen las siguientes dos funciones

int find_length(long long n)    //encontrar la cantidad de digitos
{
    int len;
    for (len = 0; n != 0; n /= 10, len++); //Loop para devolver el numero de cada digito
    return len;
    
}

//Funcion para hacer el algoritmo de Luhn
bool checksum(long long ccn)
{
    int sum = 0;
    for (int i = 0; ccn != 0; i++, ccn /= 10)
    {
        if (i % 2 == 0)
        {
            sum += ccn % 10;
        }
        else
        {
            int digit = 2 * (ccn % 10);
            sum += digit / 10 + digit % 10;
        }
    }
    return (sum % 10) == 0;
}

//Funcion para imprimir la marca de la tarjeta

void print_type(long long ccn)
{
    if ((ccn >= 34e13 && ccn < 35e13) || (ccn >= 37e13 && ccn < 38e13))
    {
        printf("AMEX\n");
    } 
    else if (ccn >= 51e14 && ccn < 56e14)
    {
        printf("MASTERCARD\n");
    } 
    else if ((ccn >= 4e12 && ccn < 5e12) || (ccn >= 4e15 && ccn < 5e15)) 
    {
        printf("VISA\n");
    } 
    else
    {
        printf("INVALID\n");
        
    }
}

