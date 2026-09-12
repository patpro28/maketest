#include "testlib.h"
#include <vector>
#include <string>

std::vector<std::pair<int, int>> limit;
int n;

std::pair<std::string, bool> readAns(InStream &stream)
{
    std::string s;

    // Read string s
    stream.readStringTo(s);
    if (s != "Yes" && s != "No")
        quitf(_wa, "Expected Yes or No, found \'%s\'", s.c_str());
    if (s == "No")
        return {s, true};
    long long sum = 0;
    for (int i = 0; i < n; ++i)
    {
        // Read x in range [l_i, r_i]
        int x = stream.readInt(limit[i].first, limit[i].second);
        sum += x;
    }
    if (sum == 0)
        return {s, true};
    return {s, false};
}

int main(int argc, char *argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    // inf - input file
    // ouf - output file
    // ans - answer file

    // Read n in range [1, 200000]
    n = inf.readInt(1, 200000, "n");

    limit.resize(n);
    for (int i = 0; i < n; ++i)
    {
        limit[i].first = inf.readInt(-1000000000, 1000000000, "l_i");
        limit[i].second = inf.readInt(-1000000000, 1000000000, "r_i");
    }

    // Read data until EOF
    float point = 1;
    while (!ans.seekEof() && !ouf.seekEof())
    {
        auto [ansStr, ______] = readAns(ans);
        auto [oufStr, isZero] = readAns(ouf);
        if (ansStr != oufStr) {
            quitf(_wa, "Expected %s, found %s", ansStr.c_str(), oufStr.c_str());
        }
        if (!isZero)
            quitf(_wa, "Expected sum to be zero, found non-zero sum");
        else
            point = 0.5;
    }

    if (ans.seekEof() && ouf.seekEof())
    {
        // Parity point
        if (point < 1)
            quitp(point, "Wrong arrays");
        quitf(_ok, "%d tests passed", 1);
    }
    else
    {
        if (ans.seekEof())
            quitf(_wa, "Participant output contains extra tokens");
        else
            quitf(_wa, "Unexpected EOF in the participants output");
    }
}
