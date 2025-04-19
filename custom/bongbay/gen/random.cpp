#include <iostream>
#include <vector>
#include <string>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string s = gen.lower_string(gen.uniform<int>(10, 1000));
    // print uppercase
    for (auto c : s) {
        cout << (char)toupper(c);
    }
    cout << '\n';
    return 0;
}
