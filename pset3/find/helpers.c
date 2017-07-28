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
    int min = 0;
    int max = n - 1;
    int middle = (min + max) / 2;
    while (min <= max)
    {
        if (values[middle] < value)
            min = middle + 1;
        else if (values[middle] > value)
            max = middle - 1;
        else if (values[middle] == value)
            return true;
        middle = (min + max) / 2;
    }
     
    if (min > max)
        return false;
     
    return false;
}
 
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (values[i] > values[j])
            {
                int temp;
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
                 
    // TODO: implement an O(n^2) sorting algorithm
    return;
}
