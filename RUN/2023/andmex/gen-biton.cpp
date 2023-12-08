#include "testlib.h"
#include <cassert>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int t = opt<int>("T");
    int n = opt<int>("N");
    int k = opt<int>("K");
    println(t);
    for(int i = 0; i < t; i++) {
        vector<int> A;
        println(n);
        for(int j = 0; j < n; j++) {
            int tmp = 0;
            for(int x = 0, y = 1; x < 30; x++, y <<= 1)
                if(x <= k || rnd.next(1, 3) == 1) tmp |= y;
            A.push_back(tmp);
        }
        println(A);
    }
    return 0;
}
