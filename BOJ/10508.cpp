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
const int P = 998244353;
const ll LLINF = (ll)1e18+1;
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

template <int MAXN>
struct eertree {
    struct Node {
        int len = 0, link = 0, cnt = 0, par = 0;
        array<int, MAXN> nxt;
        Node() { fill(nxt.begin(), nxt.end(), -1); }
    };

    vector<int> S;
    vector<Node> V;
    int root = 0;

    eertree() {
        V.resize(2);
        V[0].len = -1;
    }
    
    void add(int c) {
        S.push_back(c);
        for(int tmp = root; ; tmp = V[tmp].link) {
            auto iter = S.rbegin()+V[tmp].len+1;
            if(iter < S.rend() && *iter == c) {
                if(V[tmp].nxt[c] == -1) {
                    root = V.size();
                    V[tmp].nxt[c] = root;
                    V.push_back(Node());
                    V.back().len = V[tmp].len+2;
                    V.back().par = tmp;
                    tmp = V[tmp].link;
                    iter = S.rbegin()+V[tmp].len+1;
                    while(iter >= S.rend() || *iter != c) {
                        tmp = V[tmp].link;
                        iter = S.rbegin()+V[tmp].len+1;
                    }
                    tmp = V[tmp].nxt[c];
                    if(V.back().len == 1 || tmp <= 0) V.back().link = 1;
                    else V.back().link = tmp;
                } else root = V[tmp].nxt[c];
                V[root].cnt++;
                break;
            }
        }
    }
};

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    vector<int> M(128, INF);
    M['A'] = 0, M['C'] = 1, M['G'] = 2, M['T'] = 3;
    while(t--) {
        eertree<4> T;
        string s; cin >> s;
        for(auto c : s) T.add(M[c]);
        auto &V = T.V;
        int n = V.size();
        vector<int> link(n, 0); link[1] = 1;
        vector<int> halflink(n, 0); halflink[1] = 1;
        vector<vector<int>> sparse(n, vector<int>(21, 0));
        fill(sparse[1].begin(), sparse[1].end(), 1);
        vector<int> half(n, INF), cost(n, INF);
        half[0] = 0, half[1] = 0; cost[0] = 0, cost[1] = 0;

        int ans = (int)s.size();
        for(int i = 2; i < n; i++) {
            if(V[V[i].link].len%2 == 0) link[i] = V[i].link;
            else link[i] = link[V[i].link];
            if(V[i].len%2) continue;
            sparse[i][0] = link[i];
            for(int j = 1; j <= 20; j++)
                sparse[i][j] = sparse[sparse[i][j-1]][j-1];
            int tmp = i;
            for(int j = 20; j >= 0; j--)
                if(V[sparse[tmp][j]].len > V[i].len/2)
                    tmp = sparse[tmp][j];
            halflink[i] = link[tmp];
            half[i] = min(half[V[i].par]+1, cost[halflink[i]]+V[i].len/2-V[halflink[i]].len);
            cost[i] = min(cost[V[i].par]+2, min(half[i]+1, cost[link[i]]+V[i].len-V[link[i]].len));
            ans = min(ans, cost[i]+(int)s.size()-V[i].len);
        }
        cout << ans << "\n";
    }
    return 0;
}
