#include "testlib.h"

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 100'000, "n");
    inf.readEoln();
    inf.readEof();
}
