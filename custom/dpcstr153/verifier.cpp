#include <algorithm>
#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int k = inf.readInt(K_MIN, K_MAX, "K"); inf.readEoln();
    int total = 0, shortest = int(TOTAL_MAX) + 1;
    for (int i = 0; i < k; ++i) {
        std::string s = inf.readToken("[a-z]{1,100000}", "S_i"); inf.readEoln();
        total += s.size(); shortest = std::min(shortest, int(s.size()));
    }
    ensuref(total <= TOTAL_MAX, "Total length exceeds limit");
    ensuref(shortest <= SHORT_MAX, "At least one string must have length <= 20");
    inf.readEof();
}
