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
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

bool chk3(vector<int>& A, int i) {
    if(A[i-2] == A[i-1] || A[i-1] == A[i]) return false;
    if(A[i-2] < A[i-1] && A[i-1] < A[i]) return false;
    if(A[i-2] > A[i-1] && A[i-1] > A[i]) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        int cnt = 2*n-1;
        for(int i = 2; i < n; i++) { if(chk3(A, i)) cnt++; }
        for(int i = 3; i < n; i++) {
            if(!chk3(A, i-1)) continue;
            if(!chk3(A, i)) continue;
            swap(A[i-1], A[i]);
            if(!chk3(A, i-1)) {
                swap(A[i-1], A[i]);
                continue;
            }
            swap(A[i-1], A[i]);
            swap(A[i-3], A[i-2]);
            if(!chk3(A, i)) {
                swap(A[i-3], A[i-2]);
                continue;
            }
            swap(A[i-3], A[i-2]);
            cnt++;
        }
        cout << cnt << "\n";
    }
    return 0;
}