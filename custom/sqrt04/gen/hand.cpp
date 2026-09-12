#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(450, 500);
    cout << n << " ";
    vector<pair<int,int>> queries;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            queries.emplace_back(i, j);
    for (auto p : queries)
        cout << p.first << " " << p.second << "\n";

    return 0;
}
