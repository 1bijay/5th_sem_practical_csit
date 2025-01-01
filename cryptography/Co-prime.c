#include <stdio.h>

// Function to check if two numbers are co-prime
int coprime(int a, int b)
{
        int gcd = 1;
        for (int i = 1; i <= a; i++)
        {
                if (a % i == 0 && b % i == 0)
                {
                        gcd = i;
                }
        }
        return gcd == 1;
}

int main()
{
        int a, b;

        // Get input from the user
        printf("Enter first number : \n");
        scanf("%d", &a);
        printf("Enter second number: \n ");
        scanf("%d", &b);

        // Check if the numbers are co-prime and print the result
        if (coprime(a, b))
        {
                printf("%d and %d are co-prime\n", a, b);
        }
        else
        {
                printf("%d and %d are not co-prime\n", a, b);
        }

        return 0;
}
