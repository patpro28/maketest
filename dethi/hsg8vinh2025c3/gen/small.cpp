#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100;
    int p = 1000;
    cout << n << " " << p << endl;
    for (int i = 0; i < n; i++) {
        cout << gen.uniform<int>(1, 100) << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << gen.uniform<int>(1, 100) << " ";
    }
    return 0;
}
