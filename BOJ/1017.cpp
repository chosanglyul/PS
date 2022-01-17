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

bool dfs(int x, vector<vector<int>>& E, vector<int>& F, vector<bool>& chk) {
    if(chk[x]) return false;
    chk[x] = true;
    for(auto i : E[x]) {
        if(F[i] == -1 || dfs(F[i], E, F, chk)) {
            F[i] = x;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n), B;
    for(auto &i : A) cin >> i;
    vector<bool> C(2020, true);
    C[0] = C[1] = false;
    for(int i = 2; i < C.size(); i++) {
        if(C[i]) {
            for(int j = 2*i; j < C.size(); j += i)
                C[j] = false;
        }
    }
    for(int i = 1; i < n; i++) {
        if(C[A[0]+A[i]]) {
            vector<int> E, O;
            for(int j = 1; j < n; j++) {
                if(j == i) continue;
                if(A[j]&1) O.push_back(A[j]);
                else E.push_back(A[j]);
            }
            if(E.size() != O.size()) continue;
            int m = E.size();
            vector<vector<int>> D(m);
            vector<int> F(m, -1);
            for(int j = 0; j < m; j++)
                for(int k = 0; k < m; k++)
                    if(C[E[j]+O[k]]) D[j].push_back(k);
            int cnt = 0;
            for(int j = 0; j < m; j++) {
                vector<bool> chk(m, false);
                if(dfs(j, D, F, chk)) cnt++;
            }
            if(cnt == m) B.push_back(A[i]);
        }
    }
    if(B.size()) {
        sort(B.begin(), B.end());
        cout << B;
    } else cout << -1 << "\n";
    return 0;
}