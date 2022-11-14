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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    string s; cin >> s;
    vector<int> SA(n);
    for(int i = 0; i < n; i++) SA[i] = i;
    sort(SA.begin(), SA.end(), [&](int a, int b) {
        for(int i = 0; i+a < n && i+b < n; i++) {
            if(s[i+a] == s[i+b]) continue;
            return s[i+a] < s[i+b];
        }
        return a > b;
    });
    vector<int> LCP(n-1, 0);
    for(int i = 1; i < n; i++) {
        int a = SA[i-1], b = SA[i];
        int &c = LCP[i-1];
        while(a+c < n && b+c < n && s[a+c] == s[b+c]) c++;
    }
    vector<pii> S;
    for(int i = 0, tmp = 0; i+m <= n; i++) {
        int mi = m == 1 ? n-SA[i] : *min_element(LCP.begin()+i, LCP.begin()+i+m-1);
        for(int j = tmp; j < mi; j++) S.push_back({j+1, i});
        tmp = *min_element(LCP.begin()+i, LCP.begin()+i+m);
    }
    sort(S.begin(), S.end());
    cout << S.size() << "\n";
    for(int i = 0; i < S[k-1].fi; i++) cout << s[i+SA[S[k-1].se]];
    cout << "\n";
    return 0;
}