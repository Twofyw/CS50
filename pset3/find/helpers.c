/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    for (int min = 0,max = n,mid = n / 2;values[mid] != value && values[mid + 1] != value;)
    {
        if (values[mid] > value)
        {
            max = mid - 1;
        }
        if (values[mid] < value)
        {
            min = mid + 1;
        }
        mid = (max + min) / 2;
        if (max - min < 2 && values[mid] != value && values[mid + 1] != value)
        {
            return false;
        }
    }
    return true;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0;i < n;i++)
    {
        int smallest = values[i];
        int smallest_i = i;
        for (int j = i + 1;j < n;j++)
        {
            if (values[j] < smallest)
            {
                smallest = values[j];
                smallest_i = j;
            }
        }
        // exchange
        values[smallest_i] = values[i];
        values[i] = smallest;
    }
    
    return;
}