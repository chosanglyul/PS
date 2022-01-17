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

vector<int> kk = {0, 0, 1, 3};
vector<pi> dd = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int exi(vector<pi>& B, pi x) {
    auto iter = lower_bound(B.begin(), B.end(), x);
    if((*iter) == x) return iter-B.begin();
    else return -1;
}

pi addi(pi x, pi y) { return {x.fi+y.fi, x.se+y.se}; }
pi subt(pi x, pi y) { return {x.fi-y.fi, x.se-y.se}; }

class point {
    public:
    pi loc;
    vector<int> T;
    vector<pi> N;
    point(int xx, int yy, string& ss) {
        loc = {xx, yy};
        for(auto &i : ss) T.push_back(i-'1');
    }
    void calc(int n, vector<pi>& B) {
        int k = T.size();
        N.resize(k*4);
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < k; j++) {
                int idx = -1;
                pi tmp = dd[i^kk[T[j]]]; tmp.fi *= 2; tmp.se *= 2;
                if(T[j] > 1 || (T[j]+i)%2 == 0) idx = exi(B, addi(loc, tmp));
                if(idx == -1) N[i*k+j] = {n, i*k+(j+1)%k};
                else N[i*k+j] = {idx, (i^kk[T[j]])*k+(j+1)%k};
            }
            bool can = false;
            for(int j = 0; j < k; j++)
                if(N[i*k+j].fi != n) can = true;
            if(!can) {
                pi tmp = dd[i]; tmp.fi *= 2; tmp.se *= 2;
                int idx = exi(B, subt(loc, tmp));
                for(int j = 0; j < k; j++) N[i*k+j] = {idx, (i^2)*k+(j+1)%k};
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<point> A;
    vector<pi> B;
    for(int i = 0; i < n; i++) {
        int xx, yy; cin >> xx >> yy;
        string ss; cin >> ss;
        A.push_back(point(xx, yy, ss));
        B.push_back({xx, yy});
    }
    sort(A.begin(), A.end(), [&](point& a, point& b) { return a.loc < b.loc; });
    sort(B.begin(), B.end());
    for(int i = 0; i < n; i++) A[i].calc(i, B);
    pi loc; cin >> loc.fi >> loc.se;
    char c; cin >> c;
    ll t; cin >> t;

    pi sta = {-1, (c == '+' ? 2*k : 0)};
    if(loc.fi&1) sta.se += k;
    sta.fi = exi(B, addi(loc, dd[sta.se/k]));
    //cout << sta << "\n";

    vector<pi> C;
    vector<vector<int>> chk(n, vector<int>(4*k, -1));
    for(int i = 0; i <= 4*n*k; i++) {
        C.push_back(sta);
        if(i == t) break;
        if(chk[sta.fi][sta.se] == -1) {
            chk[sta.fi][sta.se] = i;
            sta = A[sta.fi].N[sta.se];
        } else {
            ll j = chk[sta.fi][sta.se];
            ll dt = i-j;
            ll tt = (t-j)%dt+j;
            sta = C[tt];
            break;
        }
        //cout << sta << "\n";
    }
    cout << subt(A[sta.fi].loc, dd[sta.se/k]) << "\n";
    return 0;
}