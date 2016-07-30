#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// good habit
#define BIGA 65
#define SMALLA 97

int main(int argc, string argv[])
{
    // CheckValid
    if (argc != 2)
    {
        printf("yell\n");
        return 1;
    }
    
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            return 1;
        }
    }
    
    // good k
    int k = atoi(argv[1]) % 26;
    if (k < 0)
    {
        return 1;
    }
    
    // get text
    string plaint = GetString();
    
    // caesar
    for (int i = 0, n = strlen(plaint); i < n; i++)
    {
        // ready for index
        char cchar = plaint[i];
        int icc = (int) plaint[i];
        
        // shift
        if (isupper(cchar))
        {
            printf("%c", (char) ((icc - BIGA + k) % 26) + BIGA);
        }
        else if(islower(cchar))
        {
            printf("%c", (char) ((icc - SMALLA + k) % 26) + SMALLA);
        }
        // not letters
        else
        {
            printf ("%c",cchar);
        }
    }
    printf ("\n");
    return 0;
}