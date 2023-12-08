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

struct SCC {
    private:
    int n;
    std::vector<bool> chk;
    std::vector<std::vector<int>> E, F;

    void dfs(int x, std::vector<std::vector<int>> &E, std::vector<int> &st) {
        if(chk[x]) return;
        chk[x] = true;
        for(auto i : E[x]) dfs(i, E, st);
        st.push_back(x);
    }

    public:
    SCC(std::vector<std::vector<int>> &E) {
        n = E.size();
        this->E = E;
        F.resize(n);
        chk.resize(n, false);
        for(int i = 0; i < n; i++)
            for(auto j : E[i]) F[j].push_back(i);
    }

    std::vector<std::vector<int>> getSCC() {
        std::vector<int> st;
        std::fill(chk.begin(), chk.end(), false);
        for(int i = 0; i < n; i++) dfs(i, E, st);
        std::reverse(st.begin(), st.end());
        std::fill(chk.begin(), chk.end(), false);
        std::vector<std::vector<int>> scc;
        for(int i = 0; i < n; i++) {
            if(chk[st[i]]) continue;
            std::vector<int> T;
            dfs(st[i], F, T);
            scc.push_back(T);
        }
        return scc;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; --u, --v;
        E[u].push_back(v);
    }
    SCC scc(E);
    vector<vector<int>> ans = scc.getSCC();
    for(auto &i : ans) sort(i.begin(), i.end());
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(auto &T : ans) {
        for(auto i : T) cout << i+1 << " ";
        cout << "-1\n";
    }
    return 0;
}
