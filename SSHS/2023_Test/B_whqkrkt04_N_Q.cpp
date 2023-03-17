#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[101010];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, q; cin >> n >> k >> q;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        A[i] = x == k;
    }
    ll su = 0LL, cnt = 0LL;
    for(int i = 0, l = 0; i < q; i++) {
        int r; cin >> r;
        for(int j = l; j < r; j++) {
            if(A[j]) {
                su += cnt*(cnt+1LL)/2LL;
                cnt = 0LL;
            } else cnt++;
        }
        cout << su+cnt*(cnt+1LL)/2LL << "\n";
        l = r;
    }
    return 0;
}