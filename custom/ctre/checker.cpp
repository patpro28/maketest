// https://github.com/MikeMirzayanov/testlib/blob/master/checkers/wcmp.cpp

// The MIT License (MIT)

// Copyright (c) 2015 Mike Mirzayanov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "testlib.h"

using namespace std;

int main(int argc, char * argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(3, 200000, "n"); // n in [3, 200000]
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for (int i = 2; i <= n; ++i)
    {
        int u = inf.readInt(1, n, "u");
        int v = inf.readInt(1, n, "v");
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<int> color(1);
    while (!ouf.seekEof())
    {
        int x;
        x = ouf.readInt(1, 3, "color"); // x in [1, 3]
        color.push_back(x);
    }

    if (color.size() != n + 1)
        quitf(_wa, "Unexpected EOF in the participants output");

    int root = 0;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1) {
            root = i;
            break;
        }
    vector<int> msk(n + 1);

    auto dfs = [&](auto &&self, int u, int p) -> void {
        msk[u] |= 1 << color[u];
        for (int v : adj[u]) {
            if (v != p) 
                self(self, v, u);
            msk[u] |= 1 << color[v];
        }
        if (deg[u] == 1) {
            int cnt = __builtin_popcount(msk[u]);
            if (cnt != 2)
                quitf(_wa, "Not optimal coloring 1");
            for (auto &v: adj[p])
                msk[u] |= 1 << color[v];
            msk[u] |= 1 << color[p];
            cnt = __builtin_popcount(msk[u]);
            if (cnt != 3)
                quitf(_wa, "Not optimal coloring 2");
        } else {
            int cnt = __builtin_popcount(msk[u]);
            if (cnt != 3)
                quitf(_wa, "Not optimal coloring 3");
        }
    };
    dfs(dfs, root, -1);
    quitf(_ok, "OK");
}
