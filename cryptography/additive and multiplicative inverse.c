#include <stdio.h>

// Function to find the multiplicative inverse using the Extended Euclidean Algorithm
int multiplicativeInverse(int a, int m)
{
        int m0 = m, t, q;
        int x0 = 0, x1 = 1;

        if (m == 1)
                return 0;

        while (a > 1)
        {
                // q is quotient
                q = a / m;
                t = m;

                // m is remainder now, process same as Euclid's algorithm
                m = a % m;
                a = t;

                t = x0;
                x0 = x1 - q * x0;
                x1 = t;
        }

        // Make x1 positive
        if (x1 < 0)
                x1 += m0;

        return x1;
}

// Function to find the additive inverse
int additiveInverse(int a, int m)
{
        return (m - a) % m;
}

int main()
{
        int num, MI, AI;

        printf("Enter number to get multiplicative and additive inverses modulo 26:\n");
        scanf("%d", &num);

        // Finding multiplicative inverse
        MI = multiplicativeInverse(num, 26);

        if (MI != 0)
                printf("Multiplicative inverse of %d modulo 26 is %d\n", num, MI);
        else
                printf("%d has no multiplicative inverse modulo 26\n", num);

        // Finding additive inverse
        AI = additiveInverse(num, 26);
        printf("Additive inverse of %d modulo 26 is %d\n", num, AI);

        return 0;
}
