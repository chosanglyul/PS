#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int n, k; cin >> n >> k;
    vector<long double> A(n);
    for(auto &i : A) cin >> i;
    if(k > 1) {
        for(int i = 0; i < n; i++) {
            long double tmp = A[i], ans = 0.0;
            for(int t = 1; t <= n-k+1; t++) {
                long double ncr = k*(k-1);
                for(int j = n-t-k+2; j <= n-k; j++) ncr *= j;
                for(int j = n-t; j <= n; j++) ncr /= j;
                ans += tmp * ncr;
                tmp += A[(n+i-t)%n];
            }
            cout << ans << " ";
        }
    } else {
        long double ans = (long double)100/n;
        for(int i = 0; i < n; i++) cout << ans << " ";
    }
    cout << "\n";
    return 0;
}