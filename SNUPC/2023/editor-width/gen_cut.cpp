#include "testlib.h"
#include <cassert>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>("N");
    int k = opt<int>("K");
    int t = opt<int>("T");
    assert(n%k == 0 && k > 2 && n/k > 3);

    vector<int> A;
    if(t == 1) {
        // 1 k-1 1 k-1 1 ... k-1
        for(int i = 0; i < n/k; i++) {
            A.push_back(1);
            A.push_back(k-1);
        }
    } else if(t == 2) {
        // 1 k k k ... k-2 1
        A.push_back(1);
        for(int i = 0; i < n/k-1; i++)
            A.push_back(k);
        A.push_back(k-2);
        A.push_back(1);
    } else if(t == 3) {
        // k k ... k 1 k-2 1
        for(int i = 0; i < n/k-1; i++)
            A.push_back(k);
        A.push_back(1);
        A.push_back(k-2);
        A.push_back(1);
    } else if(t == 4) {
        // k k k ... k
        for(int i = 0; i < n/k; i++)
            A.push_back(k);
    } else if(t == 5) {
        // 1 2k-1 1 ... 2k-1 1 (k) k-1
        for(int i = 0; i < (n-k)/(2*k); i++) {
            A.push_back(1);
            A.push_back(2*k-1);
        }
        A.push_back(1);
        if(!((n/k)&1)) A.push_back(k);
        A.push_back(k-1);
    } else if(t == 6) {
        // 1 ... 1 k
        for(int i = 0; i < n-k; i++)
            A.push_back(1);
        A.push_back(k);
    } else if(t == 7) {
        // k 1 ... 1
        A.push_back(k);
        for(int i = 0; i < n-k; i++)
            A.push_back(1);
    } else if(t == 8) {
        // 1 ... 1 k 1
        for(int i = 0; i < n-k-1; i++)
            A.push_back(1);
        A.push_back(k);
        A.push_back(1);
    } else {
        // 1 2k 2k ... 2k (k) k-1
        A.push_back(1);
        for(int i = 0; i < (n-k)/(2*k); i++)
            A.push_back(2*k);
        if(!((n/k)&1)) A.push_back(k);
        A.push_back(k-1);
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
