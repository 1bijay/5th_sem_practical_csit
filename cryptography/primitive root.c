#include <stdio.h>
#include <stdbool.h>

bool isPrimitiveRoot(int g, int p)
{
        bool isRoot = true;
        bool found[p];

        for (int i = 0; i < p; i++)
        {
                found[i] = false;
        }

        int x = 1;
        for (int i = 1; i <= p - 1; i++)
        {
                x = (x * g) % p;
                if (found[x])
                {
                        isRoot = false;
                        break;
                }
                found[x] = true;
        }

        return isRoot;
}

int main()
{
        int p;
        printf("Enter a prime number: ");
        scanf("%d", &p);

        printf("Primitive roots of %d are:\n", p);
        for (int g = 2; g < p; g++)
        {
                if (isPrimitiveRoot(g, p))
                {
                        printf("%d ", g);
                }
        }
        printf("\n");

        return 0;
}
