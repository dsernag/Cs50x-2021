//Recover photos from memory card
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

#define BLOCK 512 //512 spaces, means bytes

typedef uint8_t BYTE;

//Function to return the validity of JPG file
bool is_jpg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //Check functionality
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //Read file
    FILE* input = fopen(argv[1], "r");
    
    //Check the validity of the file
    if (input == NULL) 
    {
        printf("File not found\n");
        return 1;
    }
    
    BYTE array[BLOCK]; //Creation of the buffer
    bool found_first_jpg = false; //Set to false, waiting the trigger
    int index  = 0; //Reference to the count of the photos 1 through n
    
    FILE* output;
    while(fread(array, BLOCK, 1, input)) //Loop to read every 512 bytes
    {
        if(is_jpg(array))
        {
            if(!found_first_jpg)
                found_first_jpg = true;
            else
                fclose(output);
        char filename[8]; //The terms of the jpg file
        sprintf(filename, "%03i.jpg", index++); //To keep incrementing the index photo
        output = fopen(filename, "w");
        
        if(output == NULL) //In case some error
            return 1;
            
        fwrite(array, BLOCK, 1, output);
        }
        
        //Keep searching for more jpg files
        else if (found_first_jpg) 
        {
            fwrite(array, BLOCK, 1, output);
        }
    }
    fclose(output);
    fclose(input);
}


//The function drop a logical value 

bool is_jpg(BYTE buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0 )== 0xe0;
}
