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

class unifin {
    private:
    int n, m, k;
    vector<int> P, S;
    vector<vector<int>> A;
    
    public:
    unifin(int n, int m, int k) {
        this->n = n, this->m = m, this->k = k;
        for(int i = 0; i < n; i++) {
            S.push_back(1);
            P.push_back(i);
            A.push_back(vector<int>(m, -1));
            A.back()[k] = i;
        }
    }
    int siz(int x) { return S[fin(x)]; }
    int fin(int x) {
        if(P[x] == x) return x;
        return P[x] = fin(P[x]);
    }
    int fin(int x, vector<unifin>& UF) {
        x = fin(x);
        int ans = 0;
        for(int i = 0; i < m; i++) ans += UF[i].siz(A[x][i]);
        return ans;
    }
    void uni(int x, int k, int y) { 
        x = fin(x);
        if(k == this->k) {
            P[x] = y;
            S[y] += S[x];
        } else A[x][k] = y;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p, q; cin >> n >> p >> q;
    vector<unifin> UF;
    for(int i = 0; i < p; i++) UF.push_back(unifin(n/p+(i<n%p)), p, i);
    while(q--) {

    }
    return 0;
}