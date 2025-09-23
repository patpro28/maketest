#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(50, 5000);
    int m = gen.uniform<int>(50, 5000);
    cout << gen.uniform<int>(1, 9);
    for (int i = 1; i < n; ++i)
        cout << gen.uniform<int>(0, 9);
    cout << '\n';
    for (int i = 1; i < m; ++i)
        cout << gen.uniform<int>(0, 9);
    cout << '\n';
    return 0;
}
