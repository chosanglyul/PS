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
ostream& operator<<(ostream& os, const vector<T>& v) { for(const auto &i : v) os << i << " "; os << "\n"; return os; }
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

int n, m, cnt = 1;
vector<pi> d = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vector<pi> ddd = d;
vector<char> e = {'D', 'U', 'R', 'L'};
vector<vector<vector<int>>> B;
vector<vector<vector<int>>> vis;
vector<pi> path;

bool dfs(int x, int y, int z, int de) {
    x = x%cnt;
    if(de > 100000 || y < 0 || z < 0 || y >= n || z >= m || vis[x][y][z] <= de || !B[x][y][z]) return false;
    //cout << x << " " << y << " " << z << "\n";
    vis[x][y][z] = de;
    if(y+1 == n && z+1 == m) {
        path.push_back({y, z});
        return true;
        //cout << de << "\n";
        //return false;
    }
    for(auto &i : ddd) {
        bool tmp = dfs(x+1, y+i.fi, z+i.se, de+1);
        if(tmp) {
            path.push_back({y, z});
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    vector<vector<char>> A(n, vector<char>(m));
    for(auto &i : A) {
        for(auto &j : i) {
            cin >> j;
            if('2' <= j && j <= '9') {
                int g = __gcd(cnt, j-'0');
                cnt *= (j-'0')/g;
            }
        }
    }
    for(int i = 0; i < cnt; i++) {
        vector<vector<int>> T(n, vector<int>(m, 1));
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < m; k++) {
                if(A[j][k] == '#') T[j][k] = 0;
                else if('2' <= A[j][k] && A[j][k] <= '9') {
                    T[j][k] = 0;
                    if(i%(A[j][k]-'0')) {
                        for(auto &w : d) {
                            if(j+w.fi < 0 || j+w.fi >= n || k+w.se < 0 || k+w.se >= m) continue;
                            T[j+w.fi][k+w.se] = 0;
                        }
                    }
                }
            }
        }
        B.push_back(T);
    }
    vis = vector<vector<vector<int>>>(cnt, vector<vector<int>>(n, vector<int>(m, INF)));
    bool suc = dfs(0, 0, 0, 0);
    if(suc) {
        string ans = "";
        reverse(path.begin(), path.end());
        for(int i = 0; i+1 < path.size(); i++)
            for(int j = 0; j < d.size(); j++)
                if(path[i+1] == make_pair(path[i].fi+d[j].fi, path[i].se+d[j].se)) ans += e[j];
        cout << ans.length() << "\n";
        cout << ans << "\n";
    } else cout << "OHNO\n";
    return 0;
}