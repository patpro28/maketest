#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

// Sieve of Eratosthenes to generate smallest prime factors up to MAX_N
const int MAX_N = sqrt(1e7) + 1;
vector<int> prime;
vector<bool> is_prime(MAX_N + 1, true);

void generate_primes() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAX_N; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
            for (int j = i * 2; j <= MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(5, 100);
    auto N = gen.gen_sum<int>(5e5, t, 1, 1e5);
    cout << t << "\n";
    generate_primes();
    for (int i = 0; i < t; ++i) {
        int n = N[i], m = prime.size();
        cout << n << '\n';
        vector<long long> a(n);
        for (auto &x : a) x = prime[gen.uniform(0, m - 1)];
        for (auto x : a) {
            while (true) {
                int p = prime[gen.uniform(0, m - 1)];
                if (x * p * p <= 1e7) {
                    x *= p * p;
                } else {
                    cout << x << " ";
                    break;
                }
            }
        }
        cout << "\n";
    }
    return 0;
}
