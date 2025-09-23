#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int k = gen.uniform<int>(1000, 100000);
    int n = gen.uniform<int>(2e5, 5e5);
    cout << k << '\n';
    string s = gen.lower_string(n);
    cout << s << '\n';
    return 0;
}
