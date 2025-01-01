#include <stdio.h>

// Function for Euclidean Algorithm to find GCD
int euclideanGCD(int a, int b)
{
        while (b != 0)
        {
                int temp = b;
                b = a % b;
                a = temp;
        }
        return a;
}

// Function for Extended Euclidean Algorithm
int gcdExtended(int a, int b, int *s, int *t)
{
        // Base Case
        if (a == 0)
        {
                *s = 0;
                *t = 1;
                return b;
        }

        int s1, t1; // To store results of recursive call
        int gcd = gcdExtended(b % a, a, &s1, &t1);

        // Update s and t using results of recursive call
        *s = t1 - (b / a) * s1;
        *t = s1;

        return gcd;
}

// Driver Program
int main()
{
        int s, t;
        int a, b;

        // Ask the user for input
        printf("Enter two integers:\n");
        printf("a: ");
        scanf("%d", &a);
        printf("b: ");
        scanf("%d", &b);

        // Euclidean Algorithm
        int gcd = euclideanGCD(a, b);
        printf("Euclidean Algorithm: gcd(%d, %d) = %d\n", a, b, gcd);

        // Extended Euclidean Algorithm
        int g = gcdExtended(a, b, &s, &t);
        printf("Extended Euclidean Algorithm: gcd(%d, %d) = %d, s = %d, t = %d\n", a, b, g, s, t);

        return 0;
}
