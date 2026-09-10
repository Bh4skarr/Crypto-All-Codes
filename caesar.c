#include <stdio.h>
#include <ctype.h>

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
    char text[100];
    char encrypted[100], decrypted[100];
    int key, i;

    puts("Enter message:");
    readLine(text, sizeof(text));

    puts("Enter key:");
    scanf("%d", &key);

    key %= 26;

    if(key < 0)
        key += 26;

    for(i = 0; text[i] != 0; i++)
    {
        if(isalpha((unsigned char)text[i]))
        {
            char ch = (char)toupper((unsigned char)text[i]);
            encrypted[i] = (char)((ch - 'A' + key) % 26 + 'A');
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
            decrypted[i] = (char)((encrypted[i] - 'A' - key + 26) % 26 + 'A');
        else
            decrypted[i] = encrypted[i];
    }

    decrypted[i] = 0;

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}