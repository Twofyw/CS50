#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get input
    printf("minutes:");
    int time = GetInt();
    
    // calculation
    int bottles=time * 12;
    
    // output
    printf("bottles:%i\n",bottles);
}