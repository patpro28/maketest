#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int n = gen.uniform(10, 200);
    for (int i = 0; i < n; i++) {
        cout << s[gen.uniform(0, (int)s.size() - 1)];
    }
    cout << "\n";
    return 0;
}
