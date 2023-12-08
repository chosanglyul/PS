#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

const int MAX_N = 80000 + 1;

__int128 dp[MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n=1; n<MAX_N; ++n) {
        dp[n] = n;
        dp[n] *= n;
        dp[n] *= dp[n];
        
        for (int l=2; l<=n; ) {
            int q = n/l;
            int r = n/q;
            // floor(n/x) = q인 x가 [l, r]
            dp[n] -= (__int128)(r-l+1) * dp[q];
            l = r+1;
        }
    }

    for (int i=0; i<5; ++i) {
        int n;
        cin >> n;
        auto ans = dp[n];
        string out;
        while (ans > 0) {
            out += '0' + (ans % 10);
            ans /= 10;
        }
        reverse(out.begin(), out.end());
        cout << out << '\n';
    }

    return 0;
}