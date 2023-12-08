#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int k = opt<int>(1);
    println(rnd.next((1<<(k-1))+1, min(100000, 1<<k)));
}
