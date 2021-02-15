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
const int P = 1e9+7;
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

pi dx[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, t; cin >> n >> t;
    vector<pi> A(n);
    for(auto &i : A) {
        cin >> i.fi;
        string s; cin >> s;
        if(s == "right") i.se = 1;
        else i.se = -1;
    }
    A.emplace_back(t, 0);
    int tmp = 0, idx = 0;
    pi pos = {0, 0};
    for(auto &i : A) {
        int delta = i.fi-tmp;
        pos.fi += dx[idx].fi*delta;
        pos.se += dx[idx].se*delta;
        idx = (idx+i.se+4)%4;
        tmp = i.fi;
    }
    cout << pos.fi << " " << pos.se;
    return 0;
}