#include <bits/stdc++.h>

#define LL long long
using namespace std;

clock_t start = clock();

namespace IO {
    LL readInt(LL l, LL r, char endd) {
    LL x = 0;
    char ch = getchar();
    bool first = true, neg = false;
    while (true) {
        if (ch == endd) {
            break;
        } else if (ch == '-') {
            assert(first);
            neg = true;
        } else if (ch >= '0' && ch <= '9') {
            x = (x << 1) + (x << 3) + ch - '0';
        } else {
            assert(false);
        }
        first = false;
        ch = getchar();
    }
    if (neg) x = -x;
    if (x < l || x > r) {
        cerr << l << " " << r << " " << x << " failed\n";
    }
    assert(l <= x && x <= r);
    return x;
}
    string readString(int l, int r, char endd) {
    string ret = "";
    int cnt = 0;
    while (true) {
        char g = getchar();
        assert (g != -1);
        if (g == endd) {
            break;
        }
        ++cnt;
        ret += g;
    }
    assert(l <= cnt && cnt <= r);
    return ret;
}
    LL readIntSp(LL l, LL r) {
    return readInt(l, r, ' ');
}
    LL readIntLn(LL l, LL r) {
    return readInt(l, r, '\n');
}
    string readStringSp(int l, int r) {
    return readString(l, r, ' ');
}
    string readStringLn(int l, int r) {
        return readString(l, r, '\n');
    }
}
using namespace IO;

int N = 0;
void solve() {
    int n = readIntSp(1, (int)1e6), k = readIntLn(1, n);
    N += n;
    deque<pair<int, int>> dq;
    dq.push_back({0, -1});
    for (int i=0;i<n;++i) {
        while (!dq.empty() && dq.front().second < i - k - 1) {
            dq.pop_front();
        }
        int x;
        x = readInt(0, 1000, " \n"[i==n-1]);
        int ans = (dq.empty() ? 0 : dq.front().first) + x;
        while (!dq.empty() && dq.back().first >= ans) {
            dq.pop_back();
        }
        dq.push_back({ans, i});
    }
    while (!dq.empty() && dq.front().second < n - k - 1) {
        dq.pop_front();
    }
    int ans = (!dq.empty() ? dq.front().first : 0);
    cout << ans << '\n';
}

int main() {
// Start solution here use readIntLn, readIntSp and readStringSp and readStringLn
// for reading input

    int T = readIntLn(1, (int)1e6);
    while (T--) {
        solve();
    }
// End solution here
    assert(1 <= N && N <= (int)1e6);
    assert(getchar() == EOF);
    
    cerr << fixed << setprecision(10);
    cerr << "Time taken = " << (clock() - start) / ((double)CLOCKS_PER_SEC) << " s\n";
    return 0;
}