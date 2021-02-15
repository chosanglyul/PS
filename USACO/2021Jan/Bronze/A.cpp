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
    cin.tie(0);
    vector<int> A(26);
    for(int i = 0; i < 26; i++) {
        char c; cin >> c;
        A[c-'a'] = i;
    }
    string s; cin >> s;
    vector<int> B(s.size());
    for(int i = 0; i < s.size(); i++) B[i] = A[s[i]-'a'];
    int cnt = 1;
    for(int i = 0; i < s.size()-1; i++)
        if(B[i] >= B[i+1]) cnt++;
    cout << cnt << "\n";
    return 0;
}