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

int f(int i, int j, int k, bool p) {
    vector<int> A, B;
    while(i) {
        A.push_back(i%k);
        i /= k;
    }
    while(j) {
        B.push_back(j%k);
        j /= k;
    }
    while(A.size() < B.size()) A.push_back(0);
    while(A.size() > B.size()) B.push_back(0);
    int res = 0;
    for(int idx = 0, val = 1; idx < A.size(); idx++, val *= k) {
        if(p) res += val*mod(A[idx]+B[idx], k);
        else res += val*mod(A[idx]-B[idx], k);
    }
    return res;
}

int main() {
    int t; cin >> t;
    while(t--) {
        int n, k, val = 0; cin >> n >> k;
        for(int i = 0; i < n; i++) {
            int tmp = f(0, i, k, !(i&1));
            tmp = f(tmp, val, k, true);
            cout << tmp << "\n";
            fflush(stdout);
            val = f(tmp, val, k, false);
            int r; cin >> r;
            if(r) break;
        }
    }
    return 0;
}