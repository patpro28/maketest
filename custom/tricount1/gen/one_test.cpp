#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1e9;
const int MIN = 10;
const int T_MAX = 10000;
const int N_MAX = 200000;


int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1;

    cout << t << endl;
    int limit = N_MAX / t;
    while (t--) {
        int n = limit;
        cout << n << endl;
        for (int i = 0; i < n; i++) {
            cout << gen.uniform<int>(1, (n < 10 ? MIN : MAX)) << " ";
        }
        cout << endl;
    }

    return 0;
}
