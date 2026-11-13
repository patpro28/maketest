#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, low, high, budget;
    string s;
    cin >> n >> low >> high >> budget >> s;
    const int inf = n + 1;
    const int mod = 1000000007;
    using State = pair<int, int>;
    auto combine = [](State a, State b) {
        if (a.first != b.first) return a.first < b.first ? a : b;
        return State(a.first, (a.second + b.second) % mod);
    };
    int size = 1;
    while (size <= n) size *= 2;
    vector<State> tree(2 * size, State(inf, 0));
    auto assign = [&](int i, State value) {
        i += size;
        tree[i] = value;
        while (i > 1) {
            i /= 2;
            tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
        }
    };
    auto query = [&](int left, int right) {
        State answer(inf, 0);
        for (left += size, right += size + 1; left < right; left /= 2, right /= 2) {
            if (left & 1) answer = combine(answer, tree[left++]);
            if (right & 1) answer = combine(answer, tree[--right]);
        }
        return answer;
    };
    vector<int> prefix(n + 1);
    assign(0, State(0, 1));
    int first = 0;
    State answer(inf, 0);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i - 1] + s[i - 1] - '0';
        while (prefix[i] - prefix[first] > budget) ++first;
        int left = max(first, i - high);
        int right = i - low;
        answer = left <= right ? query(left, right) : State(inf, 0);
        if (answer.first != inf) {
            ++answer.first;
            assign(i, answer);
        }
    }
    if (answer.first == inf) cout << "-1 0\n";
    else cout << answer.first << ' ' << answer.second << '\n';
}
