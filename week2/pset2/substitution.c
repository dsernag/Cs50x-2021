//Substitution for alphabet key

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

bool is_valid_key(string s);

int main(int argc, string argv[])
{
    if(argc != 2) //Debe contener segundo argumento (the key)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if(! is_valid_key(argv[1])) //Verificar por medio de la funcion 
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    string s = get_string("plaintext: ");
    string difference = argv[1];
    for (int i = 'A'; i < 'Z'; i++) //Toma la letra de la key y haya la diferencia
    {
        difference[i - 'A'] = toupper(difference[i - 'A']) - i;
    }
    
    printf("ciphertext: ");
    for(int i = 0, len = strlen(s); i < len; i++)
    {
        if(isalpha(s[i]))
        {
            s[i] = s[i] + difference[s[i] - (isupper(s[i]) ? 'A' : 'a')]; 
            printf("%c", s[i]);
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}

//Funcion para verificar la clave ingresada

bool is_valid_key(string s)
{
    int len = strlen(s); 
    if (len != 26) //Que tenga 26 caracteres
    {
        return false;
    }
    
    int freq[26] = { 0 }; //Vector de 26 espacios para contar las apariciones de cada letra
    for (int i = 0; i < len; i ++) //For para recorrer cada caracter de argv[1]
    {
        if(!isalpha(s[i])) //Que sea un caracter alfabetico
        {
            return false;
        }
        int index = toupper(s[i]) - 'A'; //Ubicacion de cada caracter s[i] "estandarizado"
        if (freq[index] > 0) 
        {
            freq[index]++; //Cuenta para ubicacion del caracter key
        }
    }
    return true;
}