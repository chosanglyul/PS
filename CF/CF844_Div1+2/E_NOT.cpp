#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
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

void pre(set<piii> &A) {
    if(A.empty()) return;
    auto iter = A.begin(); iter++;
    while(iter != A.end()) {
        auto jter = iter; jter--;
        if(iter->fi.se <= jter->fi.se) iter = A.erase(iter);
        else {
            if(iter->fi.se >= jter->fi.se && iter->fi.fi == jter->fi.fi) jter = A.erase(jter);
            iter++;
        }
    }
}

void solve(set<piii> &A, set<piii> &B, set<piii> &C) {
    auto ater = A.begin();
    while(ater != A.end()) {
        auto cter = C.upper_bound({{ater->fi.fi, INF}, INF}); 
        if(cter == C.end()) continue;
        if(cter != C.begin()) {
            --cter;
            piii aaa = *ater;
            aaa.fi.fi = cter->fi.se;
            ater = A.erase(ater);
            A.insert(aaa);
            continue;
        }
        while(cter != C.end() && cter->fi.fi < ater->fi.se) {
            piii tmp = *cter;
            if(cter->fi.se <= ater->fi.se) {
                cter = C.erase(cter);
                B.insert(tmp);
            } else {
                piii aaa = *ater;
                aaa.fi.se = tmp.fi.fi;
                ater = A.erase(ater);
                A.insert(aaa);
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        set<piii> A, B, C;
        for(int i = 0; i < n; i++) {
            int u, d; cin >> u >> d;
            piii x; x.se = i; cin >> x.fi.fi >> x.fi.se; x.fi.fi--;
            if(u == 1 && d == 1) A.insert(x);
            else if(u == 2 && d == 2) B.insert(x);
            else C.insert(x);
        }
        pre(A); pre(B); pre(C);
        solve(A, C, B);
        solve(B, C, A);
        vector<pii> H(n, {0, 0}), W(n, {0, 0});
        for(auto i : A) W[i.se] = i.fi, H[i.se] = {1, 1};
        for(auto i : B) W[i.se] = i.fi, H[i.se] = {2, 2};
        for(auto i : C) W[i.se] = i.fi, H[i.se] = {1, 2};
        for(int i = 0; i < n; i++) {
            cout << W[i].fi << " " << W[i].se << " ";
            cout << ++H[i].fi << " " << H[i].se << "\n";
        }
    }
    return 0;
}