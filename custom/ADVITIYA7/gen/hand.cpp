#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1000;
    cout << t << endl;
    while (t--) {
        int x = 1;
        for (int i = 0; i < 10; ++i) {
            int k = gen.uniform(0, 5);
            if (x * (long long)(pow(primes[i], k)) > 1000000000) continue;
            x *= int(pow(primes[i], k));
        }
        cout << x << ' ' << 200 << '\n';
        for (int i = 0; i < 200; ++i) {
            cout << gen.uniform(1, 10) << '\n';
        }
    }
    
    return 0;
}
