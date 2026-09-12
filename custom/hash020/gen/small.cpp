#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string s = gen.lower_string(20, 'm', 'n');
    string p = s;
    reverse(p.begin(), p.end());
    s += p;
    auto n = vector<int>(10, 2);
    cout << 10 << '\n';
    for (int i = 0, l = 0; i < 10; ++i) {
        cout << s.substr(l, n[i]) << '\n';
        l += n[i];
    }
    return 0;
}
