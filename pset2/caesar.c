#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
int main(int argc, string argv[])
{
    string message;
    int key;
     
    // checks if there are 2 arguments, prints a message if there aren't
    if (argc != 2)
    {
        printf("Try again! Input a single non-negative integer:\n");
        return 1;
    }
    // enciphers user's message
    else
    {
        key = atoi(argv[1]);
        message = GetString();
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            // checks if the character is a letter
            if (isalpha(message[i]))
            {
                // changes uppercase letters
                if (isupper(message[i]))
                    message[i] = ((message[i] - 65 + key) % 26) + 65;
                // changes lowercase letters
                else
                    message[i] = ((message[i] - 97 + key) % 26) + 97;
            }
            printf("%c", message[i]);
        }
        printf("\n");
        return 0;
    }
}
