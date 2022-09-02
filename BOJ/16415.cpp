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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //int n; cin >> n;
    string s; cin >> s;
    int n = s.size();
    vector<int> SA(n), R(2*n, 0);
    for(int i = 0; i < n; i++) {
        SA[i] = i;
        R[i] = s[i];
    }
    for(int i = 1; i < n; i <<= 1) {
        auto cmp = [&](int x, int y) {
            return make_pair(R[x], R[x+i]) < make_pair(R[y], R[y+i]);
        };
        sort(SA.begin(), SA.end(), cmp);
        vector<int> TR(2*n, 0);
        TR[SA[0]] = 1;
        for(int i = 1; i < n; i++) TR[SA[i]] = TR[SA[i-1]] + cmp(SA[i-1], SA[i]);
        R = TR;
    }
    vector<int> ISA(n), LCP(n, 0);
    for(int i = 0; i < n; i++) ISA[SA[i]] = i;
    for(int i = 0, j = 0; i < n; i++) {
        if(!ISA[i]) continue;
        int k = SA[ISA[i]-1];
        while(max(i, k)+j < n && s[i+j] == s[k+j]) j++;
        LCP[ISA[i]] = (j ? j-- : 0);
    }
    int idx = 0;
    for(int i = 1; i < n; i++)
        if(LCP[i] > LCP[idx])
            idx = i;
    for(int i = 0; i < LCP[idx]; i++) cout << s[SA[idx]+i];
    cout << '\n';
    return 0;
}