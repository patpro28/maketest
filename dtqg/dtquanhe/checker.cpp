#include "testlib.h"

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    int optimal = 0;
    for (int i = 0; i < n; ++i) optimal = std::max(optimal, ans.readInt(0, n - 1));

    std::vector<int> value(n);
    for (int& x : value) x = ouf.readInt(0, n - 1);
    if (!ouf.seekEof()) quitf(_wa, "Extra output");

    for (int i = 1; i <= m; ++i) {
        std::string token = inf.readToken();
        int u, v;
        char op[3] = {};
        if (sscanf(token.c_str(), "%d%2[<=>]%d", &u, op, &v) != 3) {
            quitf(_fail, "Invalid relation in input");
        }
        --u;
        --v;
        if (op[0] == '>') std::swap(u, v);
        bool valid = op[0] == '=' ? value[u] == value[v]
                   : op[1] == 0 ? value[u] < value[v] : value[u] <= value[v];
        if (!valid) quitf(_wa, "Relation %d is violated", i);
    }

    int actual = *std::max_element(value.begin(), value.end());
    if (actual > optimal) quitf(_wa, "Maximum %d exceeds the optimum %d", actual, optimal);
    if (actual < optimal) quitf(_fail, "Found a better assignment with maximum %d", actual);
    quitf(_ok, "Optimal assignment");
}
