#include <iostream>
#include <vector>
#include <map>
#include "random.h"
#include "../params.h"
using namespace std;

const int MIN_DIVISORS = 1100;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 20;
    cout << t << endl;
    map<int, int> used;
    for (int i = 0; i < t; ++i)
    {
        auto get_number_greater_than_1000_divisors = [&gen, &used]()
        {
            int n;
            int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
            while (true)
            {
                n = 1;
                for (int j = 0; j < 12; ++j)
                {
                    int exp = gen.uniform(0, 5); // exponent between 0 and 4
                    for (int k = 0; k < exp; ++k)
                    {
                        if (n > 1e9 / primes[j])
                            break;
                        n *= primes[j];
                    }
                }
                int divs = 1;
                int temp = n;
                for (int j = 0; j < 12; ++j)
                {
                    int count = 0;
                    while (temp % primes[j] == 0)
                    {
                        temp /= primes[j];
                        count++;
                    }
                    divs *= (count + 1);
                }
                if (divs > MIN_DIVISORS and !used.count(n))
                    return n;
            };
        };
        int n = get_number_greater_than_1000_divisors();
        used[n] = 0;
        cout << n << endl;
    }
    return 0;
}
