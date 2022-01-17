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
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<vector<int>> A(n+1, vector<int>(9, 0));
    for(int i = 0; i < n; i++) {
        A[i+1] = A[i];
        A[i+1][(s[i]-'a')*3+i%3]++;
    }
    while(m--) {
        int l, r; cin >> l >> r; l--;
        vector<int> B(9), C(3);
        for(int i = 0; i < 9; i++) {
            B[i] = A[r][i]-A[l][i];
            if(i < 3) C[i] = i;
        }
        int ans = 0;
        do {
            int tmp = 0;
            for(int i = 0; i < 3; i++)
                tmp += B[C[i]*3+i];
            ans = max(ans, tmp);
        } while(next_permutation(C.begin(), C.end()));
        cout << r-l-ans << "\n";
    }
    return 0;
}