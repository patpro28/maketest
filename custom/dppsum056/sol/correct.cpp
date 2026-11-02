#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

bool matches(int x) {
    if (x < 0) return false;
    long long root = static_cast<long long>(sqrt(static_cast<double>(x)));
    while (root * root < x) ++root;
    while (root * root > x) --root;
    return root * root == x;
}

int main() {
    int n, k;
    if (scanf("%d%d", &n, &k) != 2) return 0;
    vector<int> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) return 0;
        prefix[i] = prefix[i - 1] + matches(x);
    }
    int best = prefix[k], position = 1;
    for (int r = k + 1; r <= n; ++r) {
        int count = prefix[r] - prefix[r - k];
        if (count > best) {
            best = count;
            position = r - k + 1;
        }
    }
    printf("%d %d\n", best, position);
}
