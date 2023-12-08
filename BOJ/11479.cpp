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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
        V.reserve(2000005);
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
    string s; cin >> s;
    SuffixAutomaton<26> sa;
    for(auto c : s) sa.add(c-'a');
    vector<ll> cnt(sa.V.size(), 0LL); cnt[0] = 1LL;
    sa.topo([&](int x, int y, int c) {
        cnt[x] += cnt[y];
    });
    ll ans = 0LL;
    for(int i = 1; i < cnt.size(); i++)
        ans += cnt[i];
    cout << ans << "\n";
    return 0;
}