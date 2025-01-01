#include <stdio.h>
#include <stdlib.h>

#define ll long long

/*
 * Modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod)
{
        ll x = 1;
        ll y = base;
        while (exponent > 0)
        {
                if (exponent % 2 == 1)
                        x = (x * y) % mod;
                y = (y * y) % mod;
                exponent = exponent / 2;
        }
        return x % mod;
}

/*
 * Fermat's theorem for checking primality
 */
int fermat(ll p, int iterations)
{
        if (p == 1)
                return 0;
        if (p == 2 || p == 3)
                return 1;
        if (p % 2 == 0)
                return 0;

        for (int i = 0; i < iterations; i++)
        {
                ll a = rand() % (p - 1) + 1;
                if (modulo(a, p - 1, p) != 1)
                {
                        return 0;
                }
        }
        return 1;
}

/*
 * Euler's totient function
 */
ll eulerTotient(ll n)
{
        ll result = n;
        for (ll p = 2; p * p <= n; ++p)
        {
                if (n % p == 0)
                {
                        while (n % p == 0)
                                n /= p;
                        result -= result / p;
                }
        }
        if (n > 1)
                result -= result / n;
        return result;
}

/*
 * Main function
 */
int main()
{
        ll num;
        int iterations = 50;

        printf("Enter an integer to test primality: ");
        scanf("%lld", &num);

        if (fermat(num, iterations))
                printf("%lld is prime according to Fermat's theorem.\n", num);
        else
                printf("%lld is composite according to Fermat's theorem.\n", num);

        printf("Euler's totient function phi(%lld) = %lld\n", num, eulerTotient(num));

        return 0;
}
