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
const ll LLINF = 1e18+1;

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

vector<int> S, SCC;
vector<vector<int>> VS, ES, E, I;

bool cmp(vector<int>& A, vector<int>& B) { return A[0] < B[0]; }

void dfs1(int x, vector<bool>& visit) {
    if(visit[x]) return;
    visit[x] = true;
    for(auto &i : E[x]) dfs1(i, visit);
    S.push_back(x);
}

void dfs2(int x, vector<bool>& visit) {
    if(visit[x]) return;
    visit[x] = true;
    VS.back().push_back(x);
    for(auto &i : I[x]) dfs2(i, visit);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int v, e; cin >> v >> e;
    E.resize(v), I.resize(v);
    for(int i = 0; i < e; i++) {
        int x, y; cin >> x >> y;
        x--, y--;
        E[x].push_back(y);
        I[y].push_back(x);
    }
    vector<bool> visit(v, false);
    for(int i = 0; i < v; i++)
        if(!visit[i]) dfs1(i, visit);
    visit = vector<bool>(v, false);
    while(S.size()) {
        int x = S.back();
        if(!visit[x]) {
            VS.push_back(vector<int>());
            dfs2(x, visit);
            sort(VS.back().begin(), VS.back().end());
        }
        S.pop_back();
    }
    sort(VS.begin(), VS.end(), cmp);
    cout << VS.size() << "\n";
    for(auto &i : VS) {
        for(auto j : i) cout << j+1 << " ";
        cout << "-1\n";
    }
    return 0;
}