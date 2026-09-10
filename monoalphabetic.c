#include <stdio.h>
#include <ctype.h>
#include <string.h>

static void readLine(char *buf, int size)
{
    int i;

    if(fgets(buf, size, stdin) == NULL)
    {
        buf[0] = 0;
        return;
    }

    for(i = 0; buf[i] != 0; i++)
    {
        if(buf[i] == 10 || buf[i] == 13)
        {
            buf[i] = 0;
            break;
        }
    }
}

int main()
{
    char text[100], key[27];
    char encrypted[100], decrypted[100];
    int i, j;

    puts("Enter message:");
    readLine(text, sizeof(text));

    puts("Enter 26 letter key:");
    readLine(key, sizeof(key));

    if(strlen(key) != 26)
    {
        puts("Invalid key");
        return 0;
    }

    for(i = 0; i < 26; i++)
        key[i] = (char)toupper((unsigned char)key[i]);

    key[26] = 0;

    for(i = 0; text[i] != 0; i++)
    {
        if(isalpha((unsigned char)text[i]))
        {
            char ch = (char)toupper((unsigned char)text[i]);
            encrypted[i] = key[ch - 'A'];
        }
        else
        {
            encrypted[i] = text[i];
        }
    }

    encrypted[i] = 0;

    for(i = 0; encrypted[i] != 0; i++)
    {
        if(isalpha((unsigned char)encrypted[i]))
        {
            for(j = 0; j < 26; j++)
            {
                if(key[j] == encrypted[i])
                {
                    decrypted[i] = (char)('A' + j);
                    break;
                }
            }
        }
        else
        {
            decrypted[i] = encrypted[i];
        }
    }

    decrypted[i] = 0;

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}