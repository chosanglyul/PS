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

vector<int> dx = {-1, 0, 0, 1};
vector<int> dy = {0, -1, 1, 0};

void add(vector<vector<int>>& A, set<pi>& B, int x, int y) {
    if(A[x][y] != -1) return;
    A[x][y] = 0;
    for(int i = 0; i < 4; i++) {
        if(A[x+dx[i]][y+dy[i]] != -1) {
            A[x][y]++;
            if(A[x+dx[i]][y+dy[i]] == 3)
                B.erase({x+dx[i], y+dy[i]});
            A[x+dx[i]][y+dy[i]]++;
            if(A[x+dx[i]][y+dy[i]] == 3)
                B.insert({x+dx[i], y+dy[i]});
        }
    }
    if(A[x][y] == 3) B.insert({x, y});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> A;
    set<pi> B, C;
    for(int i = 0; i < 5050; i++) 
        A.push_back(vector<int>(5050, -1));
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x += 2000, y += 2000;
        C.erase({x, y});
        add(A, B, x, y);
        while(B.size()) {
            pi tmp = *B.begin();
            for(int j = 0; j < 4; j++) {
                if(A[tmp.fi+dx[j]][tmp.se+dy[j]] == -1) {
                    add(A, B, tmp.fi+dx[j], tmp.se+dy[j]);
                    C.insert({tmp.fi+dx[j], tmp.se+dy[j]});
                }
            }
        }
        cout << C.size() << "\n";
    }
    return 0;
}