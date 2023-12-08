#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    setName("checker-magic-tools");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    int ansk = ans.readInt();
    int outk = ouf.readInt(0, ansk, "k");
    if(ansk < outk) quitf(_wa, "expected %d, found %d", ansk, outk);

    int m = ouf.readInt(1, n, "m");
    vector<vector<int>> P(outk);
    for(int i = 0; i < outk; i++) {
        P[i] = ouf.readIntegers(m, 0, n-1, "card");
        sort(P[i].begin(), P[i].end());
        P[i].erase(unique(P[i].begin(), P[i].end()), P[i].end());
        if(P[i].size() != m) quitf(_wa, "not unique card");
    }

    vector<int> A(n, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0, k = 1; j < outk; j++, k <<= 1) {
            auto iter = lower_bound(P[j].begin(), P[j].end(), i);
            if(iter != P[j].end() && *iter == i) A[i] += k;
        }
    }

    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    if(A.size() != n) quitf(_wa, "have same value");

    if(ansk > outk) quitf(_fail, "expected %d, found %d", ansk, outk);
    else quitf(_ok, "answer is %d", ansk);
}
