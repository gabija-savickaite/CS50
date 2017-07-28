#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 
int main(int argc, string argv[])
{
    string message, keyword;
    int j = -1;
    keyword = argv[1];
     
    // checks for 2 arguments
    if (argc != 2)
    {
        printf("Input a keyword, composed of alphabetical characters.\n");
        return 1;
    }
     
    // checks if keyword contains only letters
    for (int i = 0, n = strlen(keyword); i < n; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("Input a keyword, composed of alphabetical characters.\n");
            return 1;
        }
    }
             
     
    // enciphers user's message
    if (argc == 2)
    {
        message = GetString();
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            // changes all alphabetical chars in the message
            if (isalpha(message[i]))
            {
                j = (j + 1) % strlen(keyword);
                // changes uppercase letters
                if (isupper(message[i]))
                    message[i] = ((message[i] - 65 + toupper(keyword[j]) - 65) % 26) + 65;
                // changes lowercase letters
                else
                    message[i] = ((message[i] - 97 + toupper(keyword[j]) - 65) % 26) + 97;
            }
            printf("%c", message[i]);
        }
    }
    printf("\n");
    return 0;
}
