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

int solve() {
    int n; cin >> n;
    vector<int> A(26, -1);
    vector<bool> B(A.size(), false), C(A.size(), false);
    vector<bool> chk(A.size(), false), se(A.size(), false);
    vector<string> S(n);
    for(auto &s : S) {
        cin >> s;
        if(s.front() != s.back()) {
            se[s.front()-'a'] = true;
            se[s.back()-'a'] = true;
        }
        for(int i = 1; i < s.size(); i++) {
            if(s[i-1] != s[i]) {
                if(A[s[i-1]-'a'] > -1) return 0;
                else {
                    A[s[i-1]-'a'] = s[i]-'a';
                    C[s[i]-'a'] = true;
                }
            } else B[s[i]-'a'] = true;
        }
    }
    int cnt = 0;
    for(int i = 0; i < A.size(); i++) {
        if(!C[i] && A[i] > -1) {
            int tmp = i;
            while(tmp > -1) {
                if(chk[tmp]) return 0;
                chk[tmp] = true;
                tmp = A[tmp];
            }
            cnt++;
        }
    }
    for(int i = 0; i < A.size(); i++)
        if(C[i] || A[i] > -1)
            if(!chk[i]) return 0;
    vector<ll> F(1, 1LL);
    for(ll i = 1LL; i <= 100LL; i++)
        F.push_back((F.back()*i)%P);
    vector<int> E(A.size(), 0);
    vector<bool> f(A.size(), false);
    for(auto &s : S) {
        if(s.front() == s.back()) {
            int t = s.front()-'a';
            if(!chk[t]) {
                if(!f[t]) cnt++;
                f[t] = true;
            } else if(!se[t]) return 0;
            E[t]++;
        }
    }
    ll ans = F[cnt];
    for(auto i : E) ans = (ans*F[i])%P;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for(int i = 1; i <= t; i++)
        cout << "Case #" << i << ": " << solve() << "\n";
    return 0;
}