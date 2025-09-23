#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 1000);
    int m = gen.uniform(1, 1000);
    int q = gen.uniform(1, 1000000);
    cout << n << ' ' << m << ' ' << q << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << gen.uniform(1, 5000) << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < q; i++) {
       cout << gen.uniform(1, 10000) << '\n';
    }
    return 0;
}
