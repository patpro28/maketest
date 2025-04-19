#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int A, B;
    auto sqr = [](int x) { return 1LL * x * x; };
    auto sum = [&](int x, int y) { return sqr(x) + sqr(y) + sqr(gcd(x, y)) + sqr(lcm(x, y)); };
    do {
        A = gen.uniform(1, 100000);
        B = gen.uniform(1, 100000);
    } while (lcm(A, B) > 100000 || sum(A, B) > 1e10);

    cout << sum(A, B) << endl;
    return 0;
}
