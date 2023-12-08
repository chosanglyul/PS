#include "testlib.h"
#include <cassert>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>("N");
    int k = opt<int>("K");

    vector<int> A;
    // (1 .. k)*
    int cnt = n;
    while(cnt) {
        A.push_back(rnd.next(1, min(cnt, k)));
        cnt -= A.back();
    }

    println(n, k);
    int x = rnd.next(0, 25);
    for(auto i : A) {
        x = (x+rnd.next(1, 25))%26;
        for(int j = 0; j < i; j++) cout << (char)('a'+x);
    }
    cout << endl;

    return 0;
}
