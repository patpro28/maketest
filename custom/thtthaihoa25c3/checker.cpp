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
#include <deque>

using namespace std;

int main(int argc, char * argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    deque<int> a, b;

    while (!ans.seekEof() && !ouf.seekEof()) 
    {
        int x;
        x = ans.readInt();
        a.push_back(x);
        x = ouf.readInt();
        b.push_back(x);
    }

    if (ans.seekEof() && ouf.seekEof())
    {
        if (a[0] != b[0])
            quitf(_wa, "Expected %d, found %d", a[0], b[0]);
        int k = b[0];
        b.pop_front();
        for (auto x : b) 
        {
            if (x < 1 || x > k)
                quitf(_wa, "Invalid color %d", x);
        }
        vector<bool> sieve(n + 2, true);
        sieve[1] = false;
        bool ok = true;
        for (int i = 2; i <= n + 1; i++)
        {
            if (sieve[i])
                for (int j = 2 * i; j <= n + 1; j += i) {
                    sieve[j] = false;
                    if (b[i - 2] == b[j - 2]) ok = false;
                }
        }
        if (!ok) quitf(_wa, "Invalid coloring");
        quitf(_ok, "OK");
    }
    else
    {
        if (ans.seekEof())
            quitf(_wa, "Participant output contains extra tokens");
        else
            quitf(_wa, "Unexpected EOF in the participants output");
    }
}
