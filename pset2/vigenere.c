#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// good habit
#define BIGA 65
#define SMALLA 97

bool CheckValid(int, char**);
int ShiftsToGo(void);
int GetIdx(char);

// make universal
string k;
int kwh = 0;

int main(int argc, string argv[])
{
    // checkvaili
    if (!CheckValid(argc,argv))
    {
        return 1;
    }
    // get text
    string plaint = GetString();
    
    // vigenere
    // check
    for (int i = 0, n = strlen(plaint); i < n; i++)
    {
        // ready for index
        char cchar = plaint[i];
        int icc = (int) plaint[i];
        int kin;
        // shift + print
        if (isupper(cchar))
        {
            kin = ShiftsToGo();
            printf("%c", (char) ((icc - BIGA + kin) % 26) + BIGA);
        }
        else if(islower(cchar))
        {
            kin = ShiftsToGo();
            printf("%c", (char) ((icc - SMALLA + kin) % 26) + SMALLA);
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

bool CheckValid(int argc, string argv[])
{
    // check valid arg
    if (argc != 2)
    {
        printf("yell\n");
        return 0;
    }
    
    // check k alpha
    k = argv[1];
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("yell\n");
            return 0;
        }
    }
    // valid
    return 1;
}

int ShiftsToGo(void)
{
    // index loop
    kwh = (kwh + 1) % strlen(k);
    // 0 is last
    if (kwh == 0)
    {
        return(GetIdx(k[strlen(k) - 1]));
    }
    else
    {
        return(GetIdx(k[kwh - 1]));
    }
}

// letter to ascii shift
int GetIdx(char cchar)
{
    if (isupper(cchar))
    {
        return((int) cchar - BIGA);
    }
    else
    {
        return((int) cchar - SMALLA);
    }
}