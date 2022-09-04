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
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;

int myabs(int x) {
    if(x < 0) return -x;
    else return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int tt = 0; tt < t; tt++) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        vector<pi> B(n);
        for(int i = 0; i < n; i++) {
            cin >> B[i].fi;
            B[i].se = i;
        }
        sort(B.begin(), B.end());
        ll ans = 0LL;
        for(int i = 0; i < n; i++)
            ans += myabs(A[i] - A[B[i].se]);
        cout << "Case #" << tt+1 << endl;
        cout << ans << endl;
    }
    return 0;
}