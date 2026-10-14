#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
int main(int, char* argv[]) {
    const vector<vector<int>> cases = {
        {1}, {2}, {1000000000}, {1,1}, {2,2}, {1,2},
        {1,1,1}, {2,2,2}, {3,4,5}, {1,2,3,4,5},
        {5,4,3,2,1}, {1,1,2,2,3,3}, {1,2,4},
        {1,2,4,5}, {1,1,1,1,1,1,1}, {2,3,4,5,6,7}
    };
    auto a = cases.at(atoi(argv[1]));
    cout << a.size() << '\n';
    for (size_t i = 0; i < a.size(); ++i) cout << a[i] << (i+1 == a.size() ? '\n' : ' ');
}
