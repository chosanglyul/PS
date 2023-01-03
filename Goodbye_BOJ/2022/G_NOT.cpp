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
const int P = 998244353;
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

typedef class uf {
    private:
    vector<int> P;

    public:
    uf(int n) {
        for(int i = 0; i < n; i++) P.push_back(i);
    }
    int fin(int i) {
        if(P[i] == i) return P[i];
        return P[i] = fin(P[i]);
    }
    void uni(int i, int j) {
        i = fin(i), j = fin(j);
        if(i != j) P[j] = i;
    }
} uf;

ll calc(vector<vector<ll>> &matrix) {
    int N = matrix.size();
    ll det = 1LL;

    for (int i = 1; i < N; ++i) {
        ll pivotElement = matrix[i][i];
        int pivotRow = i;
        for (int row = i + 1; row < N; ++row) {
            if (abs(matrix[row][i]) > abs(pivotElement)) {
                pivotElement = matrix[row][i];
                pivotRow = row;
            }
        }
        if (pivotElement == 0LL) return 0LL;
        if (pivotRow != i) {
            matrix[i].swap(matrix[pivotRow]);
            det = mod(-det, P);
        }
        det = mod(det*pivotElement, P);

        for (int row = i + 1; row < N; ++row) {
            for (int col = i + 1; col < N; ++col) {
                ll tmp = (matrix[i][col] * inv(pivotElement, P))%P;
                matrix[row][col] = mod(matrix[row][col] - matrix[row][i]*tmp, P);
            }
        }
    }

    return det;
}

void dfs(int x, vector<bool>& vis, vector<int>& T, vector<vector<int>>& E) {
    if(vis[x]) return;
    vis[x] = true;
    T.push_back(x);
    for(auto i : E[x]) dfs(i, vis, T, E);
}

ll solve(vector<pii> &D, uf &U, vector<ll> &fac) {
    vector<int> V;
    for(auto i : D) {
        V.push_back(U.fin(i.fi));
        V.push_back(U.fin(i.se));
    }
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());

    int n = V.size();
    vector<vector<int>> E(n);
    for(auto i : D) {
        i.fi = lower_bound(V.begin(), V.end(), U.fin(i.fi)) - V.begin();
        i.se = lower_bound(V.begin(), V.end(), U.fin(i.se)) - V.begin();
        if(i.fi != i.se) {
            E[i.fi].push_back(i.se);
            E[i.se].push_back(i.fi);
        }
    }

    ll ret = 1LL;
    int su = 0;
    vector<bool> vis(n, false);
    for(int i = 0; i < n; i++) {
        if(vis[i]) continue;
        vector<int> T;
        dfs(i, vis, T, E);
        sort(T.begin(), T.end());
        vector<vector<ll>> M(T.size(), vector<ll>(T.size(), 0LL));
        for(int j = 0; j < T.size(); j++) {
            M[j][j] = E[T[j]].size();
            for(auto k : E[T[j]]) {
                int idx = lower_bound(T.begin(), T.end(), k) - T.begin();
                M[j][idx]--;
            }
        }
        //cout << " " << M;
        ret = (ret*calc(M))%P;
        su += (int)T.size()-1;
    }
    return (ret*fac[su])%P;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<piii> B(m);
    vector<int> A;
    uf U(n);
    vector<ll> fac(404, 1LL);
    for(int i = 1; i < fac.size(); i++) fac[i] = (fac[i-1]*i)%P;
    for(auto &i : B) {
        cin >> i.se.fi >> i.se.se >> i.fi;
        i.se.fi--, i.se.se--;
        A.push_back(i.fi);
    }
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    vector<vector<pii>> C(A.size());
    for(auto &i : B) {
        int idx = lower_bound(A.begin(), A.end(), i.fi) - A.begin();
        C[idx].push_back(i.se);
    }
    ll ans = 1LL;
    for(auto &E : C) {
        ans = (ans*solve(E, U, fac))%P;
        for(auto i : E) U.uni(i.fi, i.se);
    }
    cout << ans << "\n";
    return 0;
}