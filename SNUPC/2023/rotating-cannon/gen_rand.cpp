#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1);
    int k = 1;
    if(n < 0) n = rnd.next(1, 50);
    else k = opt<int>(2);
    println(n*k);

    vector<int> A(n), B(n);
    for(auto &i : A) i = rnd.next(1, 1'000'000'000);
    for(auto &i : B) i = rnd.next(1, 1'000);

    vector<int> AA(n*k), BB(n*k);
    for(int i = 0; i < AA.size(); i++) AA[i] = A[i%n];
    for(int i = 0; i < BB.size(); i++) BB[i] = B[i%n];
    println(AA);
    println(BB);
}
