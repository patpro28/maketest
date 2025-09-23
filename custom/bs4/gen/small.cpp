#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 20);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        long long a = gen.uniform<long long>(-10, 10);
        while (a == 0) a = gen.uniform<long long>(-10, 10);
        cout << a << ' ';
    }
    cout << '\n';
    int t = gen.uniform(1, 20);
    cout << t << '\n';
    for (int i = 0; i < t; ++i) {
        long long a = gen.uniform<long long>(-10, 10);
        while (a == 0) a = gen.uniform<long long>(-10, 10);
        cout << a << '\n';
    }

    return 0;
}
