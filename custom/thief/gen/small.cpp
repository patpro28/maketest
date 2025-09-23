#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 10;
    int w = gen.uniform<int>(10, 500);
    int h = gen.uniform<int>(50, 100);
    cout << n << " " << w << " " << h << endl;
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform<int>(1, 50) << " " << gen.uniform<int>(1, 10) << endl;
    }
    return 0;
}
