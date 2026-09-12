#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string s = gen.lower_string(100);
    string b = gen.lower_string(gen.uniform<int>(10, 20));
    while (s.size() + b.size() <= 100000)
    {
        int pos = gen.uniform<int>(0, s.size());
        s.insert(pos, b);
    }
    cout << s.size() << " " << b.size() << " " << gen.uniform<int>(3, b.size()) << '\n';
    cout << s << '\n';
    cout << b << '\n';
    return 0;
}
