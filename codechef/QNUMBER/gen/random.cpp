#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const long long MAXN = 1e12;
const int MAXQ = 5e5;

vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = 1;
    do {
        n *= p[gen.uniform<int>(0, (int)p.size() - 1)];
    } while (n <= 1e10);
    int q = gen.uniform<int>(MAXQ/2, MAXQ);
    
    cout << n << " " << q << "\n";
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(1, 3);
        long long k = gen.uniform<long long>(1, MAXN);
        cout << t << " " << k << "\n";
    }
    return 0;
}
