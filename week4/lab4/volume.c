// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    //Utilizar los chunks de 8bites(1byte) para leer el header
    
    //Será un array de tamaño 44
    uint8_t header[HEADER_SIZE];
    //Leer el chunk de 44 bytes (1 sola vez) por cada chunk 8bits
    fread(&header, HEADER_SIZE, 1, input);
    //Pasaremos la info al output
    fwrite(&header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    
    //Mediante un while podemos definir cuando parar de leer los chunks de 16bits
    //hasta llegar al final del archivo
    
    int16_t buffer;
    
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }
    
    // Close files
    fclose(input);
    fclose(output);
}
