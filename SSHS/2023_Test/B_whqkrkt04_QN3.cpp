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
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        int cnt = 0;
        for(int l = 0; l < x; l++) {
            for(int r = l+1; r <= x; r++) {
                int can = 1;
                for(int j = l; j < r; j++) {
                    if(A[j]) {
                        can = 0;
                        break;
                    }
                }
                cnt += can;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}