//UVA10235

#include <iostream>
#include <cstdlib>
using namespace std;

int prime[1000000];

long rev( long dat )
{
    long now = 0;
    while ( dat ) {
        now *= 10;
        now += dat % 10;
        dat /= 10;
    }
    return now;
}

int main()
{
    for ( long i = 0; i < 1000000; ++i )
        prime[i] = 1;
    for ( long i = 2; i < 1000000; ++i )
        if ( prime[i] )
            for ( long j = 2 * i; j < 1000000; j += i )
                prime[j] = 0;

    long n;
    while ( cin >> n ) {
        cout << n;
        if (!prime[n])
            cout << " is not prime.\n";
        else if ( n != rev(n) && prime[rev(n)] )
            cout << " is emirp.\n";
        else
            cout << " is prime.\n";
    }
    return 0;
}