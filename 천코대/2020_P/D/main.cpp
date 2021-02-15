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
    int n; cin >> n;
    vector<pl> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    vector<ll> B(n), C(n);
    for(int i = 0; i < n; i++) {
        B[i] = A[i].fi-A[i].se;
        C[i] = A[i].fi+A[i].se;
    }
    sort(B.begin(), B.end());
    sort(C.begin(), C.end());
    for(int i = 0; i < n; i++) {
        int mi = lower_bound(C.begin(), C.end(), A[i].fi-A[i].se) - C.begin();
        int ma = upper_bound(B.begin(), B.end(), A[i].fi+A[i].se) - B.begin();
        cout << mi+1 << " " << ma << "\n";
    }
    return 0;
}