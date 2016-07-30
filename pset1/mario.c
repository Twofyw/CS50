#include <stdio.h>
#include "cs50.h"

int GetHeight(void);
void Lego(int);

int main(void)
{
    int height=GetHeight();
    // print out
    Lego(height);
}

// ask for a proper height
int GetHeight(void)
{
    int height_i;
    // make in range
    do
    {
        printf ("Height:");
        height_i = GetInt();
    }
    while(height_i < 0 || height_i > 23);
    return height_i;
}

// print out
void Lego(int height)
{
    // vertical and horizontal
    for(int vert=1;vert <= height;vert++)
    {
        for(int heig=1;heig <= height - vert;heig++)
        {
            printf(" ");
        }
        for(int heig=1;heig <= vert + 1;heig++)
        {
            printf("#");
        }
        printf("\n");
    }
    
}

