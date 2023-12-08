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

template <int MAXN>
struct SuffixAutomaton {
    struct Node {
        int nxt[MAXN];
        int len = 0, link = 0;
        Node() { memset(nxt, -1, sizeof nxt); }
    };

    int root = 0;
    vector<Node> V;
    
    SuffixAutomaton() {
        V.resize(1);
        V.back().link = -1;
    }

    void add(int c) {
        V.push_back(Node());
        V.back().len = V[root].len+1;
        int tmp = root;
        root = (int)V.size()-1;
        while(tmp != -1 && V[tmp].nxt[c] == -1) {
            V[tmp].nxt[c] = root;
            tmp = V[tmp].link;
        }
        if(tmp != -1) {
            int x = V[tmp].nxt[c];
            if(V[tmp].len+1 < V[x].len) {
                int y = x;
                x = (int)V.size();
                V.push_back(V[y]);
                V.back().len = V[tmp].len+1;
                V[y].link = x;
                while(tmp != -1 && V[tmp].nxt[c] == y) {
                    V[tmp].nxt[c] = x;
                    tmp = V[tmp].link;
                }
            }
            V[root].link = x;
        }
    }

    void topo(function<void(int, int, int)> f) {
        vector<int> indeg(V.size(), 0);
        for(auto &node : V) {
            for(auto j : node.nxt) {
                if(j == -1) continue;
                indeg[j]++;
            }
        }
        queue<int> Q;
        for(int i = 0; i < (int)indeg.size(); i++)
            if(indeg[i] == 0) Q.push(i);
        while(Q.size()) {
            int tmp = Q.front(); Q.pop();
            auto &node = V[tmp];
            for(int j = 0; j < MAXN; j++) {
                if(node.nxt[j] == -1) continue;
                f(node.nxt[j], tmp, j);
                if(--indeg[node.nxt[j]] == 0)
                    Q.push(node.nxt[j]);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    SuffixAutomaton<27> sa;
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(auto c : s) sa.add(c-'a');
        sa.add(26);
    }
    vector<ll> cnt(sa.V.size(), 0LL); cnt[0] = 1LL;
    sa.topo([&](int x, int y, int c) {
        if(c == 26) return;
        cnt[x] += cnt[y];
    });
    for(int i = 0; i < m; i++) {
        string s; cin >> s;
        int tmp = 0;
        for(auto c : s) {
            tmp = sa.V[tmp].nxt[c-'a'];
            if(tmp < 0) break;
        }
        if(tmp < 0) cout << 0 << "\n";
        else cout << cnt[tmp] << "\n";
    }
    return 0;
}
