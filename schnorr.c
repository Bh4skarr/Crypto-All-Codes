#include <stdio.h>

#define P 23
#define Q 11
#define A 2

int power(int a, int b, int mod)
{
    int result = 1;
    a %= mod;

    while (b > 0)
    {
        if (b % 2 == 1)
            result = (result * a) % mod;

        a = (a * a) % mod;
        b /= 2;
    }

    return result;
}

int main()
{
    int M, s, r;
    int v, x, e, y, x1, e1;

    printf("Enter message (integer): ");
    if (scanf("%d", &M) != 1 || M < 0)
    {
        printf("Invalid message!\n");
        return 1;
    }

    printf("Enter private key s (1-10): ");
    if (scanf("%d", &s) != 1 || s < 1 || s >= Q)
    {
        printf("Invalid private key!\n");
        return 1;
    }

    printf("Enter random number r (1-10): ");
    if (scanf("%d", &r) != 1 || r < 1 || r >= Q)
    {
        printf("Invalid random number!\n");
        return 1;
    }

    /* Public key */
    v = power(A, Q - s, P);

    /* Signature generation */
    x = power(A, r, P);
    e = (M + x) % Q;
    y = (r + s * e) % Q;

    printf("\n--- Schnorr Digital Signature ---\n");
    printf("Public key v = %d\n", v);
    printf("Commitment x = %d\n", x);
    printf("Hash e = %d\n", e);
    printf("Signature (e, y) = (%d, %d)\n", e, y);

    /* Signature verification */
    x1 = (power(A, y, P) * power(v, e, P)) % P;
    e1 = (M + x1) % Q;

    printf("Verification x' = %d\n", x1);

    if (e == e1)
        printf("Signature is VALID\n");
    else
        printf("Signature is INVALID\n");

    return 0;
}
