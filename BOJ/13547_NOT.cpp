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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int sqrtN = (int)sqrt(n);
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    int m; cin >> m;
    vector<pii> B(m);
    for(int i = 0; i < m; i++) {
        B[i].fi = i;
        cin >> B[i].se.fi >> B[i].se.se;
        B[i].se.fi--;
    }
    sort(B.begin(), B.end(), [&](pii &a, pii &b) {
        if(a.se.fi/sqrtN == b.se.fi/sqrtN) return a.se.se < b.se.se;
        else return a.se.fi/sqrtN < b.se.fi/sqrtN;
    });
    vector<int> C(m);
    int s = B[0].se.fi, e = B[0].se.se;
    map<int, int> S;
    for(int i = s; i < e; i++) {
        if(S.find(A[i]) == S.end()) S.insert({A[i], 1});
        else S[A[i]]++;
    }
    C[B[0].fi] = S.size();
    for(int i = 1; i < m; i++) {
        
        C[B[i].fi] = S.size();
    }
    for(auto &i : C) cout << i << "\n";
    return 0;
}