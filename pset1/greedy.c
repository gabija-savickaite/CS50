#include <cs50.h>
#include <stdio.h>
#include <math.h>
 
int main(void)
{
    float change1;
    int coins;
     
    // prompts user for a float greater than or equal to 0
    do
    {
        printf("O hai! How much change is owed? ");
        change1 = GetFloat();
    }
    while (change1 < 0.00);
     
    // converts dollars to cents and rounds the value
    int change = round (change1 * 100);
     
    // calculates the number of coins
    coins = change / 25;
    change = change % 25;
    coins = coins + change / 10;
    change = change % 10;
    coins = coins + change / 5;
    change = change % 5;
    coins = coins + change;
     
    // prints the number of coins
    printf("%d\n", coins);
}
