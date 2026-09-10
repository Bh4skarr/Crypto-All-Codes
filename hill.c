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

int inverse(int n)
{
    int i;

    for(i = 1; i < 26; i++)
    {
        if((n * i) % 26 == 1)
            return i;
    }

    return -1;
}

int main()
{
    char text[100], clean[100];
    char encrypted[100], decrypted[100];
    int key[2][2], inv[2][2];
    int i, n = 0;
    int det, invDet;

    puts("Enter message:");
    readLine(text, sizeof(text));

    puts("Enter 2x2 key matrix:");

    for(i = 0; i < 2; i++)
        scanf("%d %d", &key[i][0], &key[i][1]);

    for(i = 0; text[i] != 0; i++)
    {
        if(isalpha((unsigned char)text[i]))
        {
            clean[n] = (char)toupper((unsigned char)text[i]);
            n++;
        }
    }

    if(n % 2 != 0)
    {
        clean[n] = 'X';
        n++;
    }

    clean[n] = 0;

    det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = (det % 26 + 26) % 26;

    invDet = inverse(det);

    if(invDet == -1)
    {
        puts("Invalid key matrix");
        return 0;
    }

    inv[0][0] = (key[1][1] * invDet) % 26;
    inv[0][1] = (26 - (key[0][1] * invDet) % 26) % 26;
    inv[1][0] = (26 - (key[1][0] * invDet) % 26) % 26;
    inv[1][1] = (key[0][0] * invDet) % 26;

    for(i = 0; i < n; i += 2)
    {
        int a = clean[i] - 'A';
        int b = clean[i + 1] - 'A';

        encrypted[i] = (char)((key[0][0] * a + key[0][1] * b) % 26 + 'A');
        encrypted[i + 1] = (char)((key[1][0] * a + key[1][1] * b) % 26 + 'A');
    }

    encrypted[n] = 0;

    for(i = 0; i < n; i += 2)
    {
        int a = encrypted[i] - 'A';
        int b = encrypted[i + 1] - 'A';

        decrypted[i] = (char)((inv[0][0] * a + inv[0][1] * b) % 26 + 'A');
        decrypted[i + 1] = (char)((inv[1][0] * a + inv[1][1] * b) % 26 + 'A');
    }

    decrypted[n] = 0;

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}