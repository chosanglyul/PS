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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

string ev(int n, string s) {
    vector<int> A(n, 1);
    for(auto c : s) {
        switch(c) {
            case '1': for(int i = 0; i < n; i++) { A[i] = 1-A[i]; } break;
            case '2': for(int i = 0; i < n; i += 2) { A[i] = 1-A[i]; } break;
            case '3': for(int i = 1; i < n; i += 2) { A[i] = 1-A[i]; } break;
            case '4': for(int i = 0; i < n; i += 3) { A[i] = 1-A[i]; } break;
        }
    }
    string ret = "";
    for(auto c : A) ret.push_back(c+'0');
    return ret;
}

vector<int> in() {
    vector<int> A;
    while(true) {
        int x; cin >> x;
        if(x == -1) break;
        A.push_back(--x);
    }
    return A;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> A = { "", "1", "2", "3", "4", "14", "24", "34" };
    int n, c; cin >> n >> c;
    for(auto &i : A) i = ev(n, i);
    vector<int> X = in();
    vector<int> Y = in();
    set<string> S;
    for(int i = 0; i < A.size(); i++) {
        bool chk = true;
        for(auto j : X) if(A[i][j] == '0') chk = false;
        for(auto j : Y) if(A[i][j] == '1') chk = false;
        if(c == 1) {
            if(i == 0 || i == 5 || i == 6 || i == 7) chk = false;
        } else if(c == 2 && i == 4) chk = false;
        if(!chk) continue;
        S.insert(A[i]);
    }
    for(auto i : S) cout << i << "\n";
    return 0;
}