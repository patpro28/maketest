#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    int p = gen.uniform(10, 10000);
    while (!is_prime(p)) {
        p = gen.uniform(10, 10000);
    }
    string s = gen.lower_string(n, '0', '9');
    cout << n << " " << p << "\n";
    cout << s << "\n";
    return 0;
}
