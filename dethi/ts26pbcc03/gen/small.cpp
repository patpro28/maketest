#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int k = gen.uniform<int>(1, 1000);
    int n = gen.uniform<int>(10, 1000);
    cout << k << '\n';
    string s = gen.lower_string(n);
    cout << s << '\n';
    return 0;
}
