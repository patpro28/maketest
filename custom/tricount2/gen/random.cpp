#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1e9;
const int MIN = 20;
const int T_MAX = 10000;
const int N_MAX = 200000;


int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(1, T_MAX);

    cout << t << endl;
    int limit = N_MAX / t;
    while (t--) {
        int n = gen.uniform<int>(1, limit);
        cout << n << endl;
        vector<int> a;
        if (n < 10)
            a = gen.choice<int>(n, 1, MIN);
        else
            a = gen.choice<int>(n, 1, MAX);
        gen.shuffle(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
