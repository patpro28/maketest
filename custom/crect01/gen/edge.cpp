#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
int main(int, char* argv[]) {
    const vector<vector<vector<int>>> cases = {
        {{0}}, {{1}}, {{1,1,1,1,1,1}}, {{1},{1},{1},{1},{1},{1}},
        {{1,0,1,1,1,0,1}}, {{1},{0},{1},{1},{1},{0},{1}},
        {{0,0,0},{0,0,0}}, {{1,1,1},{1,1,1}},
        {{1,0,1},{0,1,0},{1,0,1}},
        {{1,1,1,1},{1,0,0,1},{1,1,1,1}},
        {{0,1,1,0},{1,1,1,1},{1,1,1,1}},
        {{1,1,1,1,1},{1,1,0,1,1},{1,1,1,1,1}}
    };
    const auto& a = cases.at(atoi(argv[1]));
    cout << a.size() << ' ' << a[0].size() << '\n';
    for (const auto& row : a)
        for (size_t j=0; j<row.size(); ++j) cout << row[j] << (j+1==row.size() ? '\n' : ' ');
}
