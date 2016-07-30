/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define HEADERSIZE 54

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    int factor = atoi(argv[1]);
    
    if (factor < 1 || factor > 100)
    {
        return 4;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != HEADERSIZE || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_n = (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // new header
    BITMAPFILEHEADER bf_n = bf;
    BITMAPINFOHEADER bi_n = bi;
    bi_n.biWidth = bi.biWidth * factor;
    bi_n.biHeight = bi.biHeight * factor;
    bi_n.biSizeImage = ((bi_n.biWidth) * sizeof(RGBTRIPLE) + padding_n) * abs(bi_n.biHeight);
    bf_n.bfSize = HEADERSIZE + bi_n.biSizeImage;


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_n, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_n, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    // iterate over infile's scanlines
    for (int i = 1, biHeight = abs(bi.biHeight); i <= biHeight * factor; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile
            for (int k = 0; k < factor; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        
        if (i % factor != 0)
        {
            fseek(inptr, (-bi.biWidth) * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        else
        {
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
        }
        for (int k = 0; k < padding_n; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
