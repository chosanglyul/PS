#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    long long n = opt<int>(1);
    if(n < 0LL) n = rnd.next(2, 500'000);
    long long k = rnd.next(0LL, n*(n-1LL)/2LL);
    if(rnd.next(1, 3) == 1 && n >= 3LL) k = rnd.next(n-3LL, n*n/4LL);
    println(n, k);
}
