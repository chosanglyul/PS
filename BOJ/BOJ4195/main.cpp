#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<string, string> ps;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = 1e18+1;

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

int fin(int i, vector<int>& p) {
    if(i == p[i]) return i;
    return p[i] = fin(p[i], p);
}

void uni(int i, int j, vector<int>& r, vector<int>& p) {
    i = fin(i, p), j = fin(j, p);
    if(i == j) return;
    p[i] = j;
    r[j] += r[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        map<string, int> M;
        int n; cin >> n;
        vector<pi> S(n);
        for(auto &i : S) {
            string s; cin >> s;
            if(M.find(s) == M.end()) M.insert({s, M.size()});
            i.fi = M[s];
            cin >> s;
            if(M.find(s) == M.end()) M.insert({s, M.size()});
            i.se = M[s];
        }
        vector<int> p(M.size()), r(M.size(), 1);
        for(int i = 0; i < M.size(); i++) p[i] = i;
        for(auto &i : S) {
            uni(i.fi, i.se, r, p);
            //cout << i.fi << " " << i.se << " " << fin(i.fi, p) << "\n";
            cout << r[fin(i.fi, p)] << "\n";
        }
    }
    return 0;
}