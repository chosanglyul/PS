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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pi> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    vector<int> B(1010101), D;
    ll tmp = 1LL;
    for(auto &i : A) {
        D.push_back(i.se-i.fi+1);
        tmp = (tmp*D.back())%P;
    }
    B[0] = tmp;
    vector<pii> C; // 어디에서, {뭘로, 몇번을}
    for(int i = 0; i < A.size(); i++) {
        vector<pi> L, R;

        C.push_back({, {, i}});
    }
    sort(C.begin(), C.end());
    int cntz = 0;
    vector<bool> chkz(n, false);
    vector<int> E = B;
    for(int i = 1, j = 0; i < B.size(); i++) {
        E[i] = E[i-1];
        while(j < C.size() && C[j].fi == i) {
            if(C[j].se.fi) {
                E[i] = E[i]/D[C[j].se.se]*C[j].se.fi;
                D[C[j].se.se] = C[j].se.fi;
                if(chkz[C[j].se.se]) cntz--;
            } else {
                chkz[C[j].se.se] = true;
                cntz++;
            }
        }
        if(cntz) B[i] = 0;
        else B[i] = E[i];
    }
    for(int i = B.size(); i > 0; i--)
        for(int j = 2*i; j <= B.size(); j += i)
            B[i-1] -= B[j-1];
    cout << B;
    int ans = 0;
    for(int i = 0; i < B.size(); i++)
        ans = (ans+((ll)(i+1)*B[i])%P)%P;
    cout << ans << "\n";
    return 0;
}