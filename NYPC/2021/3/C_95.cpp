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

vector<pi> d = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<vector<vector<bool>>> vis;
int h, w, ma = 0;
vector<vector<char>> B;
set<pi> S;
pi ss;
int sx, sy;
string filename;
int gogo = 10000;

void dfs(int x, int y, int z, vector<vector<char>>& A, int dd) {
    if(ma >= gogo) return;
    if(x < 0 || x >= h || y < 0 || y >= w) {
        if(z == -1 || S.find({x, y}) != S.end()) {
            if(dd > ma) {
                ofstream wfile(filename);
                if(wfile.is_open()) {
                    wfile << dd << "\n\n";
                    wfile << sy << " " << sx << "\n";
                    for(auto &i : A) {
                        for(auto j : i) {
                            if(j == '?') wfile << '.';
                            else wfile << j;
                        }
                        wfile << "\n";
                    }
                    wfile.close();
                } else exit(1);
                ss = {sx, sy};
                ma = dd;
                B = A;
            }
        }
        return;
    }
    if(vis[x][y][z]) return;
    vis[x][y][z] = true;
    if(A[x][y] == '.') {
        dfs(x+d[z].fi, y+d[z].se, z, A, dd+2);
    } else if(A[x][y] == '?') {
        if(dd+1 < gogo) {
            A[x][y] = '.';
            dfs(x+d[z].fi, y+d[z].se, z, A, dd+2);
            A[x][y] = '/';
            dfs(x+d[z^3].fi, y+d[z^3].se, z^3, A, dd+2);
            A[x][y] = '\\';
            dfs(x+d[z^1].fi, y+d[z^1].se, z^1, A, dd+2);
        }
        A[x][y] = (z%2 ? '|' : '-');
        dfs(-2, -2, -1, A, dd+1);
        A[x][y] = '?';
    } else if(A[x][y] == '|') {
        if(z%2 == 1) dfs(-2, -2, -1, A, dd+1);
    } else if(A[x][y] == '-') {
        if(z%2 == 0) dfs(-2, -2, -1, A, dd+1);
    } else if(A[x][y] == '/') {
        dfs(x+d[z^3].fi, y+d[z^3].se, z^3, A, dd+2);
    } else if(A[x][y] == '\\') {
        dfs(x+d[z^1].fi, y+d[z^1].se, z^1, A, dd+2);
    }
    vis[x][y][z] = false;
}

int main(int argc, char** argv) {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    cout << argc << "\n";
    if(argc == 1) filename = "out.txt";
    else filename = string(argv[1])+".txt";
    cout << filename << "\n";
    cin >> h >> w;
    vector<vector<char>> A(h, vector<char>(w));
    for(auto &i : A) for(auto &j : i) cin >> j;
    int k; cin >> k;
    vector<pi> C(k);
    for(auto &i : C) cin >> i.fi >> i.se;
    std::srand(chrono::steady_clock::now().time_since_epoch().count());
    std::random_shuffle(C.begin(), C.end());
    for(int i = 0; i < k; i++) {
        vis = vector<vector<vector<bool>>>(h, vector<vector<bool>>(w, vector<bool>(4, false)));
        int x = C[i].fi, y = C[i].se;
        cout << C[i] << "\n";
        swap(x, y);
        int z, xx, yy;
        sx = x, sy = y;
        if(x == 0) {
            xx = 0;
            yy = y>>1;
            z = 0;
        }
        if(y == 0) {
            xx = x>>1;
            yy = 0;
            z = 1;
        }
        if(x == 2*w) {
            xx = w-1;
            yy = y>>1;
            z = 2;
        }
        if(y == 2*h) {
            xx = x>>1;
            yy = h-1;
            z = 3;
        }
        //cout << xx << " " << yy << "   " << z << "   " << d[z] << "\n";
        S.insert({xx-d[z].fi, yy-d[z].se});
        dfs(xx, yy, z, A, 0);
    }
    //for(auto i : S) cout << i << "  ";
    cout << "\n" << ma << "\n";
    swap(ss.fi, ss.se);
    cout << "\n" << ss << "\n";
    for(auto &i : B) {
        for(auto j : i) {
            if(j == '?') cout << '.';
            else cout << j;
        }
        cout << "\n";
    }
    return 0;
}