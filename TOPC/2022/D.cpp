#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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

vector<pii> solve(vector<int> A) {
    int n = A.size();
    vector<pii> st, ret(n, {-1, -1});
    for(int i = 0; i < n; i++) {
        if(st.empty()) {
            if(A[i] == 0) st.push_back({0, i});
        } else {
            while(st.back().fi >= A[i]) st.pop_back();
            ret[i] = st.back();
            st.push_back({A[i], i});
        }
    }
    for(int i = 0; i < n; i++) {
        if(A[i] == 0) break;
        while(st.back().fi >= A[i]) st.pop_back();
        ret[i] = st.back();
        st.push_back({A[i], i});
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(A[i] == 0) cnt++;
    }
    if(cnt != 1) {
        cout << -1 << "\n";
        return 0;
    }
    vector<pii> R = solve(A);
    reverse(A.begin(), A.end());
    vector<pii> L = solve(A);
    reverse(L.begin(), L.end());
    for(auto &i : L) i.se = n-1-i.se;
    reverse(A.begin(), A.end());
    for(int i = 0; i < n; i++) {
        if(!(L[i].fi == A[i]-1 || R[i].fi == A[i]-1)) {
            cout << -1 << "\n";
            return 0;
        }
    }
    for(int i = 0; i < n; i++) {
        if(A[i] == 0) continue;
        if(L[i].fi == A[i]-1) {
            cout << i+1 << " " << L[i].se+1 << "\n";
        } else {
            cout << i+1 << " " << R[i].se+1 << "\n";
        }
    }
    return 0;
}
