#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100;
    cout << t << endl;
    while (t--) {
        int n = gen.uniform(1, 100);
        cout << n << endl;
        for (int i = 0; i < n; ++i)
            cout << gen.uniform('0', '1');
        cout << endl;
        for (int i = 0; i < n; ++i)
            cout << gen.uniform('0', '1');
        cout << endl;
    }
    return 0;
}
