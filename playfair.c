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

void makeMatrix(char key[], char matrix[5][5])
{
    int used[26] = {0};
    int i, j = 0;
    char ch;

    used['J' - 'A'] = 1;

    for(i = 0; key[i] != 0; i++)
    {
        ch = (char)toupper((unsigned char)key[i]);

        if(ch == 'J')
            ch = 'I';

        if(isalpha((unsigned char)ch) && used[ch - 'A'] == 0)
        {
            matrix[j / 5][j % 5] = ch;
            used[ch - 'A'] = 1;
            j++;
        }
    }

    for(i = 0; i < 26; i++)
    {
        if(used[i] == 0)
        {
            matrix[j / 5][j % 5] = (char)('A' + i);
            used[i] = 1;
            j++;
        }
    }
}

void position(char matrix[5][5], char ch, int *r, int *c)
{
    int i, j;

    if(ch == 'J')
        ch = 'I';

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            if(matrix[i][j] == ch)
            {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

void encryptPair(char a, char b, char matrix[5][5], char *x, char *y)
{
    int r1, c1, r2, c2;

    position(matrix, a, &r1, &c1);
    position(matrix, b, &r2, &c2);

    if(r1 == r2)
    {
        *x = matrix[r1][(c1 + 1) % 5];
        *y = matrix[r2][(c2 + 1) % 5];
    }
    else if(c1 == c2)
    {
        *x = matrix[(r1 + 1) % 5][c1];
        *y = matrix[(r2 + 1) % 5][c2];
    }
    else
    {
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}

void decryptPair(char a, char b, char matrix[5][5], char *x, char *y)
{
    int r1, c1, r2, c2;

    position(matrix, a, &r1, &c1);
    position(matrix, b, &r2, &c2);

    if(r1 == r2)
    {
        *x = matrix[r1][(c1 + 4) % 5];
        *y = matrix[r2][(c2 + 4) % 5];
    }
    else if(c1 == c2)
    {
        *x = matrix[(r1 + 4) % 5][c1];
        *y = matrix[(r2 + 4) % 5][c2];
    }
    else
    {
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}

int main()
{
    char key[50], text[100];
    char clean[100], pairs[150];
    char encrypted[150], decrypted[150];
    char matrix[5][5];

    int i, n = 0, p = 0;

    puts("Enter key:");
    readLine(key, sizeof(key));

    puts("Enter message:");
    readLine(text, sizeof(text));

    makeMatrix(key, matrix);

    for(i = 0; text[i] != 0; i++)
    {
        if(isalpha((unsigned char)text[i]))
        {
            clean[n] = (char)toupper((unsigned char)text[i]);

            if(clean[n] == 'J')
                clean[n] = 'I';

            n++;
        }
    }

    i = 0;

    while(i < n)
    {
        pairs[p++] = clean[i];

        if(i + 1 == n)
        {
            pairs[p++] = 'X';
            i++;
        }
        else if(clean[i] == clean[i + 1])
        {
            pairs[p++] = 'X';
            i++;
        }
        else
        {
            pairs[p++] = clean[i + 1];
            i += 2;
        }
    }

    puts("");
    puts("Playfair Matrix:");

    for(i = 0; i < 5; i++)
    {
        printf("%c %c %c %c %c\n",
               matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3], matrix[i][4]);
    }

    for(i = 0; i < p; i += 2)
    {
        encryptPair(pairs[i], pairs[i + 1], matrix, &encrypted[i], &encrypted[i + 1]);
    }

    encrypted[p] = 0;

    for(i = 0; i < p; i += 2)
    {
        decryptPair(encrypted[i], encrypted[i + 1], matrix, &decrypted[i], &decrypted[i + 1]);
    }

    decrypted[p] = 0;

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}