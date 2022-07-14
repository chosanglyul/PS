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

char x[10001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int l, m;
    cin >> l >> m;

    int cheapest = 1e9;
    vector<string> name;
    for (int i=0; i<m; ++i) {
        gets(x);
        string s = x;
        int first_comma = find(s.begin(), s.end(), ',') - s.begin();
        int second_comma = find(s.begin() + first_comma + 1, s.end(), ',') - s.begin();
        int third_comma = find(s.begin() + second_comma + 1, s.end(), ',') - s.begin();
        int fourth_comma = find(s.begin() + third_comma + 1, s.end(), ',') - s.begin();
        string mowname = s.substr(0, first_comma);
        int p = stoi(s.substr(first_comma+1, second_comma-first_comma-1));
        int c = stoi(s.substr(second_comma+1, third_comma-second_comma-1));
        int t = stoi(s.substr(third_comma+1, fourth_comma-third_comma-1));
        int r = stoi(s.substr(fourth_comma+1));
        
        int cnt = 10080 / (t+r);
        if ((ll)(min(t, 10080-cnt*(t+r)) + cnt*t) * c >= l) {
            if (p < cheapest) {
                cheapest = p;
                name.clear();
                name.push_back(mowname);
            } else if (p == cheapest) {
                name.push_back(mowname);
            }
        }
    }

    if (name.empty()) {
        cout << "no such mower";
    } else {
        for (string s: name) {
            cout << s << '\n';
        }
    }

    return 0;
}