#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
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
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    vector<int> P(10);
    P[0] = 1;
    for(int i = 1; i < P.size(); i++) P[i] = P[i-1]*10;
    
    int n, cnt = 0; cin >> n;
    while(cnt < 10 && P[cnt] <= n) cnt++;
    cout << cnt << "\n";
    vector<int> ans(10, 0);
    for(int i = 0; i < cnt; i++) {
        for(int j = 0; j < ans.size(); j++) {
            
        }        
    }
    while(cnt > 0) ans[0] -= P[--cnt];
    cout << ans;
    return 0;
}