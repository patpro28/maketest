#include <array>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    vector<char> s(n + 1);
    if (scanf("%s", s.data()) != 1) return 0;
    vector<array<int, 3>> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[i] = p[i - 1];
        ++p[i][s[i - 1] - 'a'];
    }
    while (q--) {
        int l, r;
        if (scanf("%d%d", &l, &r) != 2) return 0;
        printf("%d %d %d\n", p[r][0]-p[l-1][0], p[r][1]-p[l-1][1], p[r][2]-p[l-1][2]);
    }
}
