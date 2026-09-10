#include <stdio.h>
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
    char text[100], encrypted[100], decrypted[100];
    char rail[20][100];

    int rails, len;
    int i, j, row, direction;
    int index;

    puts("Enter message:");
    readLine(text, sizeof(text));

    puts("Enter number of rails:");
    scanf("%d", &rails);

    len = (int)strlen(text);

    if(rails <= 1 || rails > len)
    {
        puts("Invalid number of rails");
        return 0;
    }

    for(i = 0; i < rails; i++)
        for(j = 0; j < len; j++)
            rail[i][j] = 0;

    row = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        rail[row][i] = text[i];

        if(row == 0)
            direction = 1;
        else if(row == rails - 1)
            direction = -1;

        row += direction;
    }

    index = 0;

    for(i = 0; i < rails; i++)
    {
        for(j = 0; j < len; j++)
        {
            if(rail[i][j] != 0)
                encrypted[index++] = rail[i][j];
        }
    }

    encrypted[index] = 0;

    for(i = 0; i < rails; i++)
        for(j = 0; j < len; j++)
            rail[i][j] = 0;

    row = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        rail[row][i] = '*';

        if(row == 0)
            direction = 1;
        else if(row == rails - 1)
            direction = -1;

        row += direction;
    }

    index = 0;

    for(i = 0; i < rails; i++)
    {
        for(j = 0; j < len; j++)
        {
            if(rail[i][j] == '*')
                rail[i][j] = encrypted[index++];
        }
    }

    row = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        decrypted[i] = rail[row][i];

        if(row == 0)
            direction = 1;
        else if(row == rails - 1)
            direction = -1;

        row += direction;
    }

    decrypted[len] = 0;

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}