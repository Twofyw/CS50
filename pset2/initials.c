#include <stdio.h>
#include <cs50.h>
#include <string.h>

// ASCII: A = 97
#define BIGA 97

void printBig(char);

int main(void)
{
    string name=GetString();

    // print first letter
    printBig(name[0]);

    // others
    for(int i=1, lenth=strlen(name); i < lenth ; i++)
    {
        // prevent crash for a name with " "?
        if (name[i] == ' ' && i != lenth - 1)
        {
            printBig(name[i + 1]);
        }
    }
    // end with enter
    printf("\n");
}

void printBig(char letter)
{
    // ASCII shift to big letters
    if ((int) letter < BIGA)
    {
        printf("%c",letter);
    }
    else
    {
        printf("%c",(char) ((int) letter - 32));
    }
}