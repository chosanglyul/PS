#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
typedef pair<int, vector<int>> piv;
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

vector<pii> solve(vector<vector<int>>& A, int n, int m) {
    vector<piv> H(n, {0, vector<int>()}), V(m, {0, vector<int>()});
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(!A[i][j] || H[i].fi == A[i][j] || V[j].fi == A[i][j]) continue;
            if(H[i].fi && V[j].fi) return vector<pii>();
            else if(H[i].fi) V[j].fi = A[i][j];
            else if(V[j].fi) H[i].fi = A[i][j];
            else {
                if(rand()%2) H[i].fi = A[i][j];
                else V[j].fi = A[i][j];
            }
        }
    }
    for(auto &i : H) cout << i.fi << " ";
    cout << "\n";
    for(auto &i : V) cout << i.fi << " ";
    cout << "\n" << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(!A[i][j] || !H[i].fi || !V[j].fi) continue;
            else if(H[i].fi != A[i][j]) H[i].se.push_back(j);
            else if(V[j].fi != A[i][j]) V[j].se.push_back(i);
        }
    }
    cout << " " << H << " " << V << "\n";
    vector<pii> B;
    while(true) {
        int cnt = 0, rea = 0;
        for(int i = 0; i < n; i++) {
            if(H[i].fi) rea++;
            else continue;
            bool can = true;
            for(auto j : H[i].se)
                if(V[j].fi) can = false;
            if(can) {
                B.push_back({0, {i+1, H[i].fi}});
                cnt++; H[i].fi = 0;
            }
        }
        for(int i = 0; i < m; i++) {
            if(V[i].fi) rea++;
            else continue;
            bool can = true;
            for(auto j : V[i].se)
                if(H[j].fi) can = false;
            if(can) {
                B.push_back({1, {i+1, V[i].fi}});
                cnt++; V[i].fi = 0;
            }
        }
        if(rea == 0) break;
        if(cnt == 0) return vector<pii>();
    }
    reverse(B.begin(), B.end());
    return B;
}

void output(vector<pii>& B) {
    cout << B.size() << "\n";
    for(auto &i : B) {
        if(!i.fi) cout << "H";
        else cout << "V";
        cout << " " << i.se.fi << " " << i.se.se << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m));
    for(auto &i : A) for(auto &j : i) cin >> j;
    while(true) {
        vector<pii> T = solve(A, n, m);
        if(T.size()) {
            output(T);
            return 0;
        }
    }
}