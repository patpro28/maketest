#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main()
{
    int b, m;
    scanf("%d%d", &b, &m);
    array<int, 10> c;
    for (int &v : c)
        scanf("%d", &v);
    vector<vector<int>> f(b + 1, vector<int>(m, -1));
    f[0][0] = 0;
    for (int budget = 1; budget <= b; ++budget)
        for (int r = 0; r < m; ++r)
            for (int d = 0; d < 10; ++d)
                if (c[d] <= budget)
                {
                    int suffix = f[budget - c[d]][(10 * r + d) % m];
                    if (suffix >= 0)
                        f[budget][r] = max(f[budget][r], 1 + suffix);
                }
    int length = -1;
    for (int d = 1; d <= 9; ++d)
        if (c[d] <= b && f[b - c[d]][d % m] >= 0)
            length = max(length, 1 + f[b - c[d]][d % m]);
    if (length < 0)
    {
        puts(c[0] == b ? "0" : "-1");
        return 0;
    }
    string answer;
    int budget = b, r = 0;
    for (int pos = 0; pos < length; ++pos)
        for (int d = 9; d >= (pos == 0 ? 1 : 0); --d)
            if (c[d] <= budget)
            {
                int next = (10 * r + d) % m;
                if (f[budget - c[d]][next] == length - pos - 1)
                {
                    answer.push_back(char('0' + d));
                    budget -= c[d];
                    r = next;
                    break;
                }
            }
    puts(answer.c_str());
}
