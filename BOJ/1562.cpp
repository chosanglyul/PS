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
const int P = 1000000000;
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

void upd(vector<vector<int>>& A, int i) {
    A[i][0] = A[i-1][1];
    A[i][A[i].size()-1] = A[i-1][A[i].size()-2];
    for(int j = 1; j < A[i].size()-1; j++)
        A[i][j] = (A[i-1][j-1]+A[i-1][j+1])%P;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(10, 0)), B(n, vector<int>(9, 0)), C(n, vector<int>(9, 0)), D(n, vector<int>(8, 0));
    for(int i = 1; i <= 9; i++) A[0][i] = B[0][i-1] = 1;
    for(int i = 1; i <= 8; i++) C[0][i] = D[0][i-1] = 1;
    for(int i = 1; i < n; i++) {
        upd(A, i); upd(B, i); upd(C, i); upd(D, i);
    }
    ll cnt = 0LL;
    for(int i = 0; i < A.back().size(); i++) cnt = mod(cnt+A.back()[i], P);
    for(int i = 0; i < B.back().size(); i++) cnt = mod(cnt-B.back()[i], P);
    for(int i = 0; i < C.back().size(); i++) cnt = mod(cnt-C.back()[i], P);
    for(int i = 0; i < D.back().size(); i++) cnt = mod(cnt+D.back()[i], P);
    cout << cnt << "\n";
    return 0;
}