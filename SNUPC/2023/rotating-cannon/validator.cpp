#include "testlib.h"

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    inf.readIntegers(n, 1, 1'000'000'000, "a");
    inf.readEoln();

    inf.readIntegers(n, 1, 1'000, "b");
    inf.readEoln();

    inf.readEof();
}
