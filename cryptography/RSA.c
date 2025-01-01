#include <stdio.h>
#include <stdlib.h>

// Function to calculate the greatest common divisor
int gcd(int a, int b)
{
        while (b != 0)
        {
                int temp = b;
                b = a % b;
                a = temp;
        }
        return a;
}

// Function to find a coprime e
int find_coprime_e(int phi_n)
{
        int e = 2;
        while (gcd(e, phi_n) != 1)
        {
                e++;
        }
        return e;
}

// Function to find the modular inverse of a under modulo m
int mod_inverse(int a, int m)
{
        int m0 = m, x0 = 0, x1 = 1;
        while (a > 1)
        {
                int q = a / m;
                int temp = m;
                m = a % m;
                a = temp;
                temp = x0;
                x0 = x1 - q * x0;
                x1 = temp;
        }
        return (x1 + m0) % m0;
}

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
        int p, q, n, phi_n, e, d, m, c;

        // Get input for two prime numbers
        printf("Enter first prime number:\n ");
        scanf("%d", &p);
        printf("Enter second prime number:\n ");
        scanf("%d", &q);

        // Calculate n and phi_n
        n = p * q;
        phi_n = (p - 1) * (q - 1);

        // Find public and private keys
        e = find_coprime_e(phi_n);
        d = mod_inverse(e, phi_n);

        printf("Public key: (%d, %d)\n", e, n);
        printf("Private key: (%d, %d)\n", d, n);

        // Get input for the message to be encrypted
        printf("Enter a number to encrypt: ");
        scanf("%d", &m);

        // Encrypt the message
        c = mod_exp(m, e, n);
        printf("Encrypted message: %d\n", c);

        // Decrypt the message
        m = mod_exp(c, d, n);
        printf("Decrypted message: %d\n", m);

        return 0;
}
