#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

long long N_MAX = 1e18;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int tcs(long long n) {
    int res = 0;
    while (n) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n;

    do {
        n = gen.uniform<long long>(1, N_MAX - 1);
    } while (!isPrime(tcs(n)));

    string s = to_string(n);
    int pos = gen.uniform<int>(0, s.size() - 1);
    s[pos] = 'X';
    cout << s << endl;
    return 0;
}
