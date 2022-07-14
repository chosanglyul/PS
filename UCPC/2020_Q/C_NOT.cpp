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

int getnum(char c, vector<int>& A) {
    if(c == '0' || c == '1') return c-'0';
    return A[c-'a'];
}

int solve(string& s, int l, int r, vector<int>& A) {
    int q = -1, c = -1;
    for(int i = l, lvl = 0; i < r; i++) {
        if(s[i] == '?') lvl++;
        if(s[i] == ':') lvl--;
        if(q == -1 && lvl == 1) q = i;
        if(q != -1 && c == -1 && lvl == 0) c = i;
    }
    //cout << l << " " << r << " " << q << " " << c << "\n";
    if(q != -1) {
        int x = getnum(s[l], A), y = getnum(s[l+3], A);
        int ans = 0;
        bool bx = (x == -1), by = (y == -1);
        for(int i = 0; i <= 1; i++) {
            for(int j = 0; j <= 1; j++) {
                if(!bx && x != i) continue;
                if(!by && y != j) continue;
                if(bx) A[s[l]-'a'] = i;
                if(by) A[s[l+3]-'a'] = j;
                if(i == j) ans += solve(s, q+1, c, A);
                else ans += solve(s, c+1, r, A);
            }
        }
        if(bx) A[s[l]-'a'] = -1;
        if(by) A[s[l+3]-'a'] = -1;
        return ans;
    } else {
        int x = getnum(s[l], A);
        if(x == 1) return 0;
        int cnt = 0;
        for(auto i : A) if(i == -1) cnt++;
        if(x == -1) cnt--;
        return (1<<cnt);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n, -1);
    string s; cin >> s;
    cout << solve(s, 0, s.size(), A) << "\n";
    return 0;
}