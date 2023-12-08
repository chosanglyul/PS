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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
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

pii sim(int x, vector<int> &A) {
    char c = 'A';
    int y = 0;
    pii ret = {x, 0};
    while(true) {
        y += A[ret.fi++];
        if(ret.fi == A.size()) ret.se++, ret.fi = 0;
        if(c == 'A') {
            if(y == 5) y = 0, c = 'B';
            else if(y == 10) y = 0, c = 'C';
        } else if(c == 'B' && y == 3) y = 0, c = 'E';
        if(c == 'A') {
            if(y > 20) break;
        } else if(c == 'B') {
            if(y > 11) break;
        } else if(c == 'C') {
            if(y > 6) break;
        } else if(c == 'E') {
            if(y > 3) break;
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n, k; cin >> n >> k;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        vector<pii> B(n, {-1, -1}); B[0] = {0, 0};
        vector<pii> C = {{0, 0}};
        for(int x = 0, y = 0, i = 1; ; i++) {
            pii tmp = sim(x, A);
            x = tmp.fi, y += tmp.se;
            if(y > k || (y == k && x > 0)) {
                cout << i-1;
                break;
            } else if(B[x].fi < 0) {
                B[x] = {i, y};
                C.push_back({y, x});
            } else {
                C.push_back({y, x});
                ll cnt = i-B[x].fi, rot = y-B[x].se;
                ll ful = (k-B[x].se-1)/rot;
                ll ans = B[x].fi+ful*cnt;
                for(int i = B[x].fi; i < C.size(); i++, ans++) {
                    int tmp = ful*rot+C[i].fi;
                    if(tmp > k || (tmp == k && C[i].se > 0)) break;
                }
                cout << --ans;
                break;
            }
        }
        cout << endl;
    }
    return 0;
}
