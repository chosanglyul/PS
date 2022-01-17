#include <bits/stdc++.h>
using namespace std;

void fil(vector<int>& src, vector<int>& dst, int j, int x) {
    if(src[j] < 0) return;
    dst[j+x] = max(dst[j+x], src[j]+x);
    dst[j-x] = max(dst[j-x], src[j]+x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    int siz = 1010101;
    vector<int> B(siz, -1), C(siz, -1);
    B[siz>>1] = C[siz>>1] = 0;
    int mi = n>>1;
    for(int i = 0; i < mi; i++) {
        vector<int> BB(B);
        for(int j = 0; j < siz; j++)
            fil(B, BB, j, A[i]);
        B = BB;
    }
    for(int i = mi; i < n; i++) {
        vector<int> CC(C);
        for(int j = 0; j < siz; j++)
            fil(C, CC, j, A[i]);
        C = CC;
    }
    int ans = -1;
    for(int i = 0; i < siz; i++) {
        if(B[i] < 0 || C[i] < 0) continue;
        if(B[i] == 0 && C[i] == 0) continue;
        ans = max(ans, (B[i]+C[i])/2);
    }
    cout << ans << "\n";
    return 0;
}