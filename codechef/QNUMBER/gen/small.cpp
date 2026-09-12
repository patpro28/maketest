#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long MAXN = 1000;
const int MAXQ = 10;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = gen.uniform<long long>(1, MAXN);
    int q = gen.uniform<int>(1, MAXQ);
    
    cout << n << " " << q << "\n";
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(1, 3);
        long long k = gen.uniform<long long>(1, MAXN);
        cout << t << " " << k << "\n";
    }
    return 0;
}
