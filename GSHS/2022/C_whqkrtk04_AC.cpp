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

ll po(ll a, ll b) {
    ll tmp = a, ans = 1LL;
    while(b) {
        if(b&1LL) ans = (ans*tmp)%P;
        tmp = (tmp*tmp)%P;
        b >>= 1LL;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n), B(n+1, 0);
    vector<bool> vis(n, false);
    for(auto &i : A) {
        cin >> i;
        vis[--i] = true;
    }
    for(auto i : vis) {
        if(!i) {
            cout << 0 << "\n";
            return 0;
        }
    }
    fill(vis.begin(), vis.end(), false);
    for(int i = 0; i < n; i++) {
        if(vis[i]) continue;
        int tmp = i, cnt = 0;
        do {
            vis[tmp] = true;
            tmp = A[tmp];
            cnt++;
        } while(tmp != i);
        B[cnt]++;
    }
    
    vector<int> C;
    for(int i = 1; i <= min(n, k); i++)
        if(k%i == 0) C.push_back(i);
    vector<vector<ll>> DPC(n+1, vector<ll>(n+1, 0LL));
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            if(i == 0 || j == 0 || j == i) DPC[i][j] = 1LL;
            else DPC[i][j] = (DPC[i-1][j-1]+DPC[i-1][j])%P;
        }
    }
    vector<ll> I(n+1);
    for(int i = 1; i <= n; i++) I[i] = inv(i, P);
    vector<ll> fac(n+1, 1LL);
    for(int i = 1; i <= n; i++) fac[i] = (fac[i-1]*i)%P;

    ll ans = 1LL;
    for(int i = 1; i <= n; i++) {
        vector<ll> DP(B[i]+1, 0LL); DP[0] = 1LL;
        for(auto j : C) {
            if(__gcd(k/j, i) != 1) continue;
            ll cnt = (fac[j-1]*po(i, j-1))%P;
            for(int x = B[i]; x >= 0; x--) {
                ll tmp = cnt, ncr = 1LL;
                for(int y = x-j, z = 1; y >= 0; y -= j, tmp = (tmp*cnt)%P, z++) {
                    ncr = (((ncr*DPC[y+j][j])%P)*I[z])%P;
                    DP[x] = (DP[x]+((tmp*ncr)%P)*DP[y])%P;
                }
            }
        }
        ans = ((DP[B[i]]%P)*ans)%P;
    }
    cout << ans << "\n";
    return 0;
}