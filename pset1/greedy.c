#include <stdio.h>
#include <cs50.h>
#include <math.h>

float GetPosiFloat();
int Corecal(int);

int main(void)
{
    // get number
    printf("O hai!");
    float owed=GetPosiFloat();
    int owed_c=(int) round(owed * 100);
    // output
    printf("%i\n",Corecal(owed_c));
}

float GetPosiFloat()
{
    float owed_i;
    // be positive
    do
    {
        printf("How much change is owed?\n");
        owed_i = GetFloat();
    }
    while(owed_i <= 0);
    return owed_i;
}

int Corecal(int owe)
{
    // n is number of coins, i owe is currently owed between calculation
    int n=0;
    int cur[4]={25,10,5,1};
    int i=0;
    // try one by one
    do
    {
        n += owe / cur[i];
        owe %= cur[i];
        i++;
    }
    while(owe > 0);
    
    // ready for output
    return n;
}