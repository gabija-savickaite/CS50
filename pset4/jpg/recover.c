/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
  
#include <stdio.h>
#include <stdint.h>
 
int main(int argc, char* argv[])
{
    // opens card.raw
    FILE* file = fopen("card.raw", "r");
     
    // sets the output pointer to NULL
    FILE* jpg = NULL;
     
    // error handling
    if (file == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
     
    uint8_t buffer[512];
    int jpgcounter = 0;
    int openjpgcounter = 0;
    char jpgname[7];
     
    // reads 512 byte blocks while end of file has not been reached
    while (fread(&buffer, 512, 1, file) == 1)
    {
        // if jpeg signature detected
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // close the open output file if there is one
            if (openjpgcounter > 0)
                fclose(jpg);
         
            // update filename
            sprintf(jpgname, "%03d.jpg", jpgcounter);
             
            // open a new file for output
            jpg = fopen(jpgname, "a");
             
            openjpgcounter = 1;
            jpgcounter++;
             
            fwrite(&buffer, 512, 1, jpg);
             
        }
         
        else if (jpg != NULL)
            fwrite(&buffer, 512, 1, jpg); 
                  
    }
     
    // close outfile
    fclose(jpg);
     
    // close infile
    fclose(file);
     
    return 0;  
}
