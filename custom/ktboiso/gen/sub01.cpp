#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(10, 100);
    cout << t << endl;
    while (t--) {
        int a = gen.uniform<int>(1, 100);
        int b = gen.uniform<int>(1, 100);
        long long n = gen.uniform<long long>(1, 1e6);
        cout << a << " " << b << " " << n << "\n";
    }

    return 0;
}
