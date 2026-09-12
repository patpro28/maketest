#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const ull BASE = 131;

int N;
vector<string> s;
vector<ull> h, hr;
vector<int> len;
vector<ull> pw;

long long ans = 0;
bool used[10];

void dfs(ull hf, ull hr_total, int total_len) {
    if (total_len > 0 && hf == hr_total) {
        ans++;
    }

    for (int i = 0; i < N; i++) {
        if (used[i]) continue;

        used[i] = true;

        ull new_hf = hf * pw[len[i]] + h[i];
        ull new_hr = hr[i] * pw[total_len] + hr_total;

        dfs(new_hf, new_hr, total_len + len[i]);

        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    s.resize(N);

    for (int i = 0; i < N; i++) cin >> s[i];

    h.resize(N);
    hr.resize(N);
    len.resize(N);

    for (int i = 0; i < N; i++) {
        len[i] = s[i].size();

        ull cur = 0;
        for (char c : s[i]) cur = cur * BASE + c;
        h[i] = cur;

        cur = 0;
        for (int j = len[i] - 1; j >= 0; j--) {
            cur = cur * BASE + s[i][j];
        }
        hr[i] = cur;
    }

    int MAXL = 10000;
    pw.resize(MAXL + 1, 1);
    for (int i = 1; i <= MAXL; i++) pw[i] = pw[i - 1] * BASE;

    dfs(0, 0, 0);

    cout << ans << '\n';
}