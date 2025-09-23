#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

string dir[] = {"N", "S", "E", "W", "NE", "SE", "SW", "NW"};

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    cout << dir[gen.uniform<int>(0, 7)];
    return 0;
}
