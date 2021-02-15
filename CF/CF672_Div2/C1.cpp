#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, q; cin >> n >> q;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        bool deac = false;
        int cnt = 0;
        ll ans = 0;
        for(int i = 0; i < n-1; i++) {
            if(deac) {
                if(A[i] < A[i+1]) {
                    ans -= A[i];
                    deac = false;
                }
            } else {
                if(A[i] > A[i+1]) {
                    ans += A[i];
                    deac = true;
                }
            }
        }
        if(!deac) ans += A[n-1];
        cout << ans << "\n";
    }
    return 0;
}