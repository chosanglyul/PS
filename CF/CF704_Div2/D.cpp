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
    int a, b, k; cin >> a >> b >> k;
    if(k == 0) {
        cout << "Yes\n";
        string x = "";
        for(int i = 0; i < b; i++) x.push_back('1');
        for(int i = 0; i < a; i++) x.push_back('0');
        cout << x << "\n" << x << "\n";
    } else if(a == 0 || b == 1 || a+b-2 < k) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        string x = "", y = "";
        for(int i = 0; i < b; i++) x.push_back('1');
        for(int i = 0; i < a; i++) x.push_back('0');
        if(k <= a) {
            for(int i = 0; i < b-1; i++) y.push_back('1');
            for(int i = 0; i < k; i++) y.push_back('0');
            y.push_back('1');
            for(int i = 0; i < a-k; i++) y.push_back('0');
        } else {
            int t = a+b-k-1;
            for(int i = 0; i < t; i++) y.push_back('1');
            y.push_back('0');
            for(int i = 0; i < b-1-t; i++) y.push_back('1');
            for(int i = 0; i < a-1; i++) y.push_back('0');
            y.push_back('1');
        }
        cout << x << "\n" << y << "\n";
    }
    return 0;
}