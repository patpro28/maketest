#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string s = gen.lower_string(1000000, 'a', 'a');
    cout << s << '\n';
    return 0;
}
