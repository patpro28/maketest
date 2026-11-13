// Independent search of common subsequences, using simultaneous embeddings.
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    int k; cin >> k;
    vector<string> strings(k);
    for (string &s : strings) cin >> s;
    sort(strings.begin(), strings.end(), [](const string &a, const string &b) { return a.size() < b.size(); });
    const string base = strings[0];
    vector<vector<array<int, 26> > > next(k - 1);
    for (int i = 1; i < k; ++i) {
        int n = strings[i].size();
        next[i - 1].resize(n + 1);
        next[i - 1][n].fill(-1);
        for (int p = n - 1; p >= 0; --p) {
            next[i - 1][p] = next[i - 1][p + 1];
            next[i - 1][p][strings[i][p] - 'a'] = p;
        }
    }
    int answer = 0, length = base.size();
    function<void(int, int, const vector<int> &)> search = [&](int start, int chosen, const vector<int> &positions) {
        answer = max(answer, chosen);
        if (chosen + length - start <= answer) return;
        for (int j = start; j < length; ++j) {
            if (chosen + length - j <= answer) break;
            vector<int> after(k - 1);
            bool possible = true;
            for (int i = 0; i < k - 1; ++i) {
                int p = next[i][positions[i]][base[j] - 'a'];
                if (p == -1) { possible = false; break; }
                after[i] = p + 1;
            }
            if (possible) search(j + 1, chosen + 1, after);
        }
    };
    search(0, 0, vector<int>(k - 1, 0));
    cout << answer << '\n';
}
