#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;
struct Group { int height; ll count, starts; };
ll triangle(ll x) { return x * (x + 1) / 2; }

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int rows, columns; cin >> rows >> columns;
    vector<int> height(columns);
    vector<Group> stack;
    ll answer = 0;
    for (int row = 0; row < rows; ++row) {
        string s; cin >> s;
        stack.clear();
        ll total = 0, weighted = 0;
        for (int j = 1; j <= columns; ++j) {
            int h = height[j - 1] = s[j - 1] == '1' ? height[j - 1] + 1 : 0;
            ll count = 1, starts = j;
            while (!stack.empty() && stack.back().height >= h) {
                auto g = stack.back(); stack.pop_back();
                total -= triangle(g.height) * g.count;
                weighted -= triangle(g.height) * g.starts;
                count += g.count; starts += g.starts;
            }
            stack.push_back({h, count, starts});
            total += triangle(h) * count; weighted += triangle(h) * starts;
            answer += (j + 1LL) * total - weighted;
        }
    }
    cout << answer << '\n';
}
