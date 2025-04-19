#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

vector<long long> divisors(long long n) {
    vector<long long> divs;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    return divs;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long m = 1;
    vector<long long> divs = divisors(m);
    int n = 200000;
    cout << n << ' ' << m << endl;
    for (int i = 0; i < n; i++) {
        cout << divs[gen.uniform<int>(0, divs.size() - 1)] << ' ';
    }
    return 0;
}
