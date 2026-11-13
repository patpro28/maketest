#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace(); int words = inf.readInt(1, 10000, "words");
    inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    int totalLength = 0;
    for (int i = 0; i < words; ++i) {
        std::string word = inf.readToken("[a-z]{1,100}", "W");
        totalLength += int(word.size());
        inf.readSpace();
        inf.readInt(0, 1000000000, "C");
        inf.readEoln();
    }
    ensuref(totalLength <= 50000, "Total dictionary length exceeds 50000");
    inf.readEof();
}
