#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string s = "";
    while (s.size() < 1e5)
        s += gen.uniform<char>('a', 'c');
    string b = "";
    while (b.size() < 20)
        b += gen.uniform<char>('a', 'c');
    cout << s.size() << " " << b.size() << " " << gen.uniform<int>(3, b.size()) << '\n';
    cout << s << '\n';
    cout << b << '\n';
    return 0;
}
