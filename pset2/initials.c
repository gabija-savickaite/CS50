#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
int main(void)
{
    string name;
    char initials[10];
    // number of initials 
    int num = 1;
    name = GetString();
     
    // first char of "initials" is always the same as the first char of the name
    initials[0] = toupper(name[0]);
     
    // includes every letter that goes after a space into "initials" array
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] == ' ')
        {
            initials[num] = name[i + 1];
            initials[num] = toupper(initials[num]);
            num++;
        }
    }
     
    // prints initials
    for (int i = 0; i < num; i++)
        printf("%c", initials[i]);
    printf("\n");
}
