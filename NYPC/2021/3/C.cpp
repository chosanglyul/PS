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

vector<pi> d = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<vector<vector<bool>>> vis;
int h, w, sx, sy, ma;
vector<vector<char>> B, E;
set<pi> S;
pi ss;
string filename;
int edtime;

void output(ostream& os) {
    os << ma << "\n\n";
    os << ss.se << " " << ss.fi << "\n";
    for(auto &i : B) {
        for(auto j : i) {
            if(j == '?') os << '.';
            else os << j;
        }
        os << "\n";
    }
}

void dfs(int x, int y, int z, vector<vector<char>>& A, int dd) {
    if(time(nullptr) > edtime) return;
    if(x < 0 || x >= h || y < 0 || y >= w) {
        if(z == -1 || S.find({x, y}) != S.end()) {
            if(dd >= ma) {
                ss = {sx, sy}; ma = dd; B = A;
                ofstream wfile(filename);
                if(wfile.is_open()) {
                    output(wfile);
                    wfile.close();
                } else exit(1);
            }
        }
        return;
    }
    if(vis[x][y][z]) return;
    vis[x][y][z] = true;
    if(A[x][y] == '.') {
        dfs(x+d[z].fi, y+d[z].se, z, A, dd+2);
    } else if(A[x][y] == '?') {
        A[x][y] = (z%2 ? '|' : '-');
        dfs(-2, -2, -1, A, dd+1);
        vector<char> TT = {'.', '/', '\\'};
        random_shuffle(TT.begin()+1, TT.end());
        for(auto i : TT) {
            A[x][y] = i;
            if(i == '.') dfs(x+d[z].fi, y+d[z].se, z, A, dd+2);
            else if(i == '/') dfs(x+d[z^3].fi, y+d[z^3].se, z^3, A, dd+2);
            else dfs(x+d[z^1].fi, y+d[z^1].se, z^1, A, dd+2);
        }
        A[x][y] = '?';
    } else if(A[x][y] == '|') {
        if(z%2 == 1) dfs(-2, -2, -1, A, dd+1);
    } else if(A[x][y] == '-') {
        if(z%2 == 0) dfs(-2, -2, -1, A, dd+1);
    } else if(A[x][y] == '/') {
        if(E[x][y] == '/') dfs(x+d[z^3].fi, y+d[z^3].se, z^3, A, dd+2);
    } else if(A[x][y] == '\\') {
        if(E[x][y] == '\\') dfs(x+d[z^1].fi, y+d[z^1].se, z^1, A, dd+2);
    }
    vis[x][y][z] = false;
}

int main(int argc, char** argv) {
    if(argc == 1) filename = "out.txt";
    else filename = string(argv[1])+".txt";
    cin >> h >> w;
    vector<vector<char>> A(h, vector<char>(w));
    for(auto &i : A) for(auto &j : i) cin >> j;
    E = A;
    int k; cin >> k;
    vector<pi> C(k);
    for(auto &i : C) cin >> i.fi >> i.se;
    std::srand(chrono::steady_clock::now().time_since_epoch().count());
    std::random_shuffle(C.begin(), C.end());
    for(int j = 0, tt = 1; j < 8; j++, tt *= 10) {
        vector<pi> D;
        for(int i = 0; i < C.size(); i++) {
            edtime = time(nullptr)+tt;
            vis = vector<vector<vector<bool>>>(h, vector<vector<bool>>(w, vector<bool>(4, false)));
            int x = C[i].se, y = C[i].fi, z, xx, yy;
            sx = x, sy = y;
            if(x == 0) { xx = 0; yy = y>>1; z = 0; }
            if(y == 0) { xx = x>>1; yy = 0; z = 1; }
            if(x == 2*w) { xx = w-1; yy = y>>1; z = 2; }
            if(y == 2*h) { xx = x>>1; yy = h-1; z = 3; }
            S.insert({xx-d[z].fi, yy-d[z].se});
            dfs(xx, yy, z, A, 0);
            if(time(nullptr) > edtime) D.push_back(C[i]);
        }
        C = D;
        cout << D;
    }
    output(cout);
    return 0;
}