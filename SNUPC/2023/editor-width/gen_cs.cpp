#include "testlib.h"
#include <cassert>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int k = opt<int>("K");
    int n = 5*k-1;
    assert(k >= 3);

    int cnt;
    vector<int> A;
    cnt = k;
    while(cnt) {
        A.push_back(rnd.next(1, min(cnt, k-1)));
        cnt -= A.back();
    }
    A.push_back(k);
    cnt = 2*k-1;
    while(cnt) {
        A.push_back(rnd.next(1, min(cnt, k-1)));
        cnt -= A.back();
    }
    A.push_back(k);

    println(n, k);
    int x = rnd.next(0, 25);
    for(auto i : A) {
        x = (x+rnd.next(1, 25))%26;
        for(int j = 0; j < i; j++) cout << (char)('a'+x);
    }
    cout << endl;

    return 0;
}
