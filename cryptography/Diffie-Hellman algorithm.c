#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to perform modular exponentiation
int mod_exp(int base, int exp, int mod)
{
        int result = 1;
        base = base % mod;
        while (exp > 0)
        {
                if (exp % 2 == 1)
                {
                        result = (result * base) % mod;
                }
                exp = exp >> 1;
                base = (base * base) % mod;
        }
        return result;
}

int main()
{
        int prime = 23;
        int generator = 5;
        int XA, XB, YA, YB;
        int shared_secret_userA, shared_secret_userB;

        // Seed the random number generator
        srand(time(NULL));

        // Generate private keys
        XA = rand() % (prime - 1) + 1;
        XB = rand() % (prime - 1) + 1;

        // Compute public keys
        YA = mod_exp(generator, XA, prime);
        YB = mod_exp(generator, XB, prime);

        // Compute shared secrets
        shared_secret_userA = mod_exp(YB, XA, prime);
        shared_secret_userB = mod_exp(YA, XB, prime);

        // Print results
        printf("Prime (p): %d\n", prime);
        printf("Generator (g): %d\n", generator);
        printf("userA's private key (a): %d\n", XA);
        printf("userB's private key (b): %d\n", XB);
        printf("userA's public key (A): %d\n", YA);
        printf("userB's public key (B): %d\n", YB);
        printf("Shared secret computed by userA: %d\n", shared_secret_userA);
        printf("Shared secret computed by userB: %d\n", shared_secret_userB);

        return 0;
}
