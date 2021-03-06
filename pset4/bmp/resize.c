/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP file.
 */
        
#include <stdio.h>
#include <stdlib.h>
 
#include "bmp.h"
 
int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    if (*argv[1] < 1 || *argv[1] > 100)
    {
        printf("Please enter a positive integer less than or equal to 100.");
        return 2;
    }
     
    // remember n
    int n = atoi(argv[1]);
     
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
 
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }
 
    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }
 
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
     
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
     
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }    
     
    int biHeight = bi.biHeight;
    int biWidth = bi.biWidth;
     
    // change bitmap's data
    bi.biHeight = bi.biHeight * n;
    bi.biWidth = bi.biWidth * n;
     
    // determine padding for scanlines
    int padding2 =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding2) * abs(bi.biHeight);
    bf.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + (bi.biSizeImage);
     
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
     
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
 
    // iterate over infile's scanlines
    for (int i = 0, height = abs(biHeight); i < height; i++)
    {
        for (int row = 0; row < n; row++)
        {
            if (row != 0)
                fseek(inptr, -(sizeof(RGBTRIPLE) * biWidth + padding), SEEK_CUR);
             
            // iterate over pixels in scanline
            for (int j = 0; j < biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
 
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
 
                // write RGB triple to outfile
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                 
            }
 
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
         
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
         
        }
 
    }
 
    // close infile
    fclose(inptr);
 
    // close outfile
    fclose(outptr);
 
    // that's all folks
    return 0;
}
