#include<bits/stdc++.h>
using namespace std;

const int M = 5e5 + 1;

int n, m;
string a[M];
int len[M] = {0};

void Update(int pos, int val) {
    while (pos <= n) {
        len[pos] += val;
        pos += pos & -pos;
    }
    return;
}

int Sum(int pos) {
    int res = 0;
    while (pos > 0) {
        res += len[pos];
        pos -= pos & -pos;
    }
    return res;
}

int Get(int l, int r) {
    return Sum(r) - Sum(l - 1);
}

int BS(int l, int r, int k) {
    int tmp = l;
    int res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (Get(tmp, mid) >= k) {
            res = mid;
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        Update(i, a[i].size());
    }
    string task, s;
    int idx, l, r, k;
    while (m--) {
        cin >> task;
        if (task == "update") {
            cin >> idx >> s;
            Update(idx, s.size() - a[idx].size());
            a[idx] = s;
        }else {
            cin >> l >> r >> k;
            if (Get(l, r) < k) {
                cout << -1 << '\n';
                continue;
            }
            int prev = BS(l, r, k);
            int i = a[prev].size() - (Get(l, prev) - k) - 1;
            cout << a[prev][i] << '\n';            
        }
    }
    return 0;
}