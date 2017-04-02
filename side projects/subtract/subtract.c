//
//  main.c
//  subtract
//
//  Created by Twofyw Yang on 4/1/17.
//  Copyright © 2017 Twofyw Yang. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define BASE '0'

void stripe0(char*, int, int);
int swap(char*, char*);

int main(int argc, const char * argv[]) {
    // get input
    char a[82], b[82];
    printf("A: ");
    fgets(a, 81, stdin);
    printf("B: ");
    fgets(b, 81, stdin);
    int adig = (int) strlen(a);
    int bdig = (int) strlen(b);
    
    // stripe tailing \n
    a[adig-1] = '\0';
    b[bdig-1] = '\0';
    // stripe leading 0s
    stripe0(a, adig-1, 0);
    stripe0(b, bdig-1, 0);
    
    // put the bigger number to a
    int swapped = 0;
    adig = (int) strlen(a);
    bdig = (int) strlen(b);
    if (adig < bdig) swapped = swap(a, b);
    else if (adig == bdig) {
        if (strcmp(a, b) < 0) swapped = swap(a, b);
        if (strcmp(a, b) == 0) {
            printf("0\n");
            return 0;
        }
    }
    adig = (int) strlen(a);
    bdig = (int) strlen(b);
    
    // subtract
    // padding
    char zeros[81];
    for (int i  = 0; i < adig - bdig; i++) {
        strcat(zeros, "0");
    }
    strcat(zeros, b);
    strcpy(b, zeros);
    char output[adig+1+swapped];
    int borr = 0;
    for (int i = adig-1; i>=0; i--) {
        if(a[i]-borr >= b[i]){
            output[i+swapped] = (char) (BASE + a[i]-borr - b[i]);
            borr = 0;
        }
        else{
            output[i+swapped] = (char) (BASE + a[i]-borr+10 - b[i]);
            borr = 1;
        }
    }
    
    if(swapped) output[0] = '-';
    output[adig+swapped] = '\0';
    // stripe leading 0s after (if any) negation sign
    stripe0(output, adig+swapped, swapped);
    
    printf("%s\n", output);
    return 0;
}

void stripe0(char* s, int len, int beg){
    int first_encountered = 0;
    for (int i=beg, j=beg; (s[j]=s[i]) && i < len; j += (s[i++]!=BASE || first_encountered)) {
        first_encountered += s[i] - BASE;
    }
}

int swap(char* f, char* s){
    char tmp[80];
    strcpy(tmp, f);
    strcpy(f, s);
    strcpy(s, tmp);
    return 1;
}
