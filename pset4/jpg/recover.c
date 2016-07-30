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

typedef uint8_t BYTE;

#define BLOCKSIZE 512

int main(void)
{
    BYTE buffer[BLOCKSIZE];
    FILE* tmpf;
    char filename[8];
    FILE* inptr = fopen("card.raw", "r");
    int fi = -1;
    int recording = 0;
    while (fread(&buffer, sizeof(BYTE), BLOCKSIZE, inptr) == BLOCKSIZE)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && buffer[3] / 16 == 0xE)
        {
            if (recording == 0)
            {
                fi++;
                sprintf(filename, "%03d.jpg", fi);
                tmpf = fopen(filename, "w");
                recording = 1;
                fwrite(&buffer, sizeof(BYTE), BLOCKSIZE, tmpf);
            }
            else
            {
                fclose(tmpf);
                fi++;
                sprintf(filename, "%03d.jpg", fi);
                tmpf = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCKSIZE, tmpf);
            }
        }
        else if(recording == 1)
        {
            fwrite(&buffer, sizeof(BYTE), BLOCKSIZE, tmpf);
        }
    }
    fclose(tmpf);
    fclose(inptr);
}