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
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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

const pii v[4] = { {1,0},{-1,0},{0,1},{0,-1} };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int r, c;
    cin >> r >> c;
    string ring;
    cin >> ring;
    vector<string> board(r);
    for (string& s: board) cin >> s;

{
    vector<vector<int>> ok(r, vector<int>(c, 0));
    for (int i=0; i<r; ++i) {
        for (int j=0; j<c; ++j) {
            bool okay = true;
            for (int k=0; k<c; ++k) {
                if (ring[k] == '1') {
                    if (board[i][(j+k)%c] == '1') {
                        okay = false;
                        break;
                    }
                }
            }
            ok[i][j] = okay;
        }
        // cout << ok[i];
    }

    vector<vector<int>> visited(r, vector<int>(c, 0));
    queue<pii> q;
    for (int i=0; i<c; ++i) {
        if (ok[0][i]) {
            q.push({ 0, i });
            visited[0][i] = 1;
        }
    }
    while (!q.empty()) {
        auto[x, y] = q.front();
        q.pop();
        // cout << x << ' ' << y << endl;
        for (auto dv: v) {
            int dx = x + dv.first;
            int dy = y + dv.second;
            if (0 <= dx && dx < r) {
                if (dy == -1) dy = c-1;
                if (dy == c) dy = 0;
                if (!visited[dx][dy] && ok[dx][dy]) {
                    q.push({ dx, dy });
                    visited[dx][dy] = 1;
                }
            }
        }
    }
    for (int i=0; i<c; ++i) {
        if (visited[r-1][i]) {
            cout << 'Y';
            return 0;
        }
    }
}

    reverse(ring.begin(), ring.end());

{
    vector<vector<int>> ok(r, vector<int>(c, 0));
    for (int i=0; i<r; ++i) {
        for (int j=0; j<c; ++j) {
            bool okay = true;
            for (int k=0; k<c; ++k) {
                if (ring[k] == '1') {
                    if (board[i][(j+k)%c] == '1') {
                        okay = false;
                        break;
                    }
                }
            }
            ok[i][j] = okay;
        }
        // cout << ok[i];
    }

    vector<vector<int>> visited(r, vector<int>(c, 0));
    queue<pii> q;
    for (int i=0; i<c; ++i) {
        if (ok[0][i]) {
            q.push({ 0, i });
            visited[0][i] = 1;
        }
    }
    while (!q.empty()) {
        auto[x, y] = q.front();
        q.pop();
        // cout << x << ' ' << y << endl;
        for (auto dv: v) {
            int dx = x + dv.first;
            int dy = y + dv.second;
            if (0 <= dx && dx < r) {
                if (dy == -1) dy = c-1;
                if (dy == c) dy = 0;
                if (!visited[dx][dy] && ok[dx][dy]) {
                    q.push({ dx, dy });
                    visited[dx][dy] = 1;
                }
            }
        }
    }
    for (int i=0; i<c; ++i) {
        if (visited[r-1][i]) {
            cout << 'Y';
            return 0;
        }
    }
}

    cout << 'N';

    return 0;
}
