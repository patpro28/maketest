#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int>& A) {
    int n = (int) A.size();
    if (n < 2) {
        return {};
    }

    vector<int> X;
    set<int> S;
    S.insert(A[0]);
    S.insert(A[1]);

    vector<int> res;
    res.reserve(n - 1);
    map<int,int> M;
    int ans = 0;

    auto INSERT = [&](int l, int r) {
        auto it = M.lower_bound(l);
        int ll = l, rr = r;
        if (it != M.begin()) {
            auto [l1, r1] = *prev(it);
            if (max(ll, l1) <= min(rr, r1)) {
                ll = min(ll, l1);
                rr = max(rr, r1);
                it = M.erase(prev(it));    
                ans -= r1 - l1;    
            }        
        }
        while (it != M.end()) {
            auto [l1, r1] = *it;
            if (max(ll, l1) <= min(rr, r1)) {
                ll = min(ll, l1);
                rr = max(rr, r1);
                it = M.erase(it);
                ans -= r1 - l1;
            } else {
                break;
            }
        }
        M[ll] = rr;
        ans += rr - ll;
    };


    {
        int l = abs(A[0] - A[1]) + 1;
        int r = A[0] + A[1];
        INSERT(l, r);
        res.push_back(ans);
    }

    for (int i = 2; i < n; ++i) {
        int x = A[i];
        auto it = S.lower_bound(x);
        if (it != S.end()) {
            int y = *it;
            int l = y - x + 1;
            int r = y + x;
            INSERT(l, r);
        }
        if (it != S.begin()) {
            int y = *prev(it);
            int l = x - y + 1;
            int r = x + y;
            INSERT(l, r);
        }
        res.push_back(ans);
        S.insert(x);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int t;
    cin >> t;
    while (t-- > 0) {
        int n;
        cin >> n;
        vector<int> A(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }

        auto res = solve(A);
        for (auto x : res) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}