#include <cs50.h>
#include <stdio.h>
 
int main(void)
{
    int height;
    int spaces;
    // prompts the user for an integer between 0 and 23
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
     
    // number of spaces in the first line is one less than pyramid's height
    spaces = height - 1;
     
    // prints the half-pyramid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 2; j++)
        {
            printf("#");
        }
        // number of spaces decreases on each line
        spaces--;
        printf("\n");
    }
     
}
