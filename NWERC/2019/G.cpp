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

    cout << fixed << setprecision(13);

    int n, k;
    cin >> n >> k;
    vector<double> s(n);
    for (double& x: s) cin >> x;
    if (k == 1) {
        for (int i=0; i<n; ++i) {
            cout << 100.0/n << ' ';
        }
        return 0;
    }

    vector<double> ans(n, 0.0);
    for (int i=0; i<n; ++i) {
        double ratio = (double)k*(k-1)/n/(n-1);
        double p = 0;
        for (int r=0; r<=n-k; ++r) {
            p += s[(i-r+n)%n];
            ans[i] += p * ratio;
            ratio = ratio * (n-k-r) / (n-r-2);
        }
    }
    for (int i=0; i<n; ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}