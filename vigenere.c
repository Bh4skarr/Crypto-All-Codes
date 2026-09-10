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
    char text[100], key[100];
    char encrypted[100], decrypted[100];
    int i, j = 0, k;

    puts("Enter message:");
    readLine(text, sizeof(text));

    puts("Enter key:");
    readLine(key, sizeof(key));

    k = (int)strlen(key);

    if(k == 0)
    {
        puts("Invalid key");
        return 0;
    }

    for(i = 0; key[i] != 0; i++)
        key[i] = (char)toupper((unsigned char)key[i]);

    for(i = 0; text[i] != 0; i++)
    {
        if(isalpha((unsigned char)text[i]))
        {
            char ch = (char)toupper((unsigned char)text[i]);

            while(!isalpha((unsigned char)key[j % k]))
                j++;

            encrypted[i] = (char)((ch - 'A' + toupper((unsigned char)key[j % k]) - 'A') % 26 + 'A');
            j++;
        }
        else
        {
            encrypted[i] = text[i];
        }
    }

    encrypted[i] = 0;

    j = 0;

    for(i = 0; encrypted[i] != 0; i++)
    {
        if(isalpha((unsigned char)encrypted[i]))
        {
            while(!isalpha((unsigned char)key[j % k]))
                j++;

            decrypted[i] = (char)((encrypted[i] - 'A' - (toupper((unsigned char)key[j % k]) - 'A') + 26) % 26 + 'A');
            j++;
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