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
struct eertree {
    struct Node {
        int nxt[MAXN];
        int len = 0, link = 0, cnt = 0;
        Node() { memset(nxt, -1, sizeof nxt); }
    };

    vector<int> S, roots;
    vector<Node> V;
    int root = 0;

    eertree() {
        V.resize(2);
        V[0].len = -1;
    }
    
    void add(int c) {
        assert(0 <= c && c < MAXN);
        S.push_back(c);
        for(int tmp = root; ; tmp = V[tmp].link) {
            auto iter = S.rbegin()+V[tmp].len+1;
            if(iter < S.rend() && *iter == c) {
                if(V[tmp].nxt[c] == -1) {
                    root = V.size();
                    V[tmp].nxt[c] = root;
                    V.push_back(Node());
                    V.back().len = V[tmp].len+2;
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
        roots.push_back(root);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    eertree<26> tree;
    int n; cin >> n;
    deque<char> s(n);
    for(auto &c : s) cin >> c;
    string t;
    for(int i = 0; s.size(); i++) {
        if(i%2) { t.push_back(s.back()); s.pop_back(); }
        else { t.push_back(s.front()); s.pop_front(); }
    }
    reverse(t.begin(), t.end());
    // cout << t << "\n";
    for(auto c : t) tree.add(c-'a');
    // cout << tree.roots;
    auto &V = tree.V;
    vector<int> evenlink(V.size(), 0); evenlink[1] = 1;
    for(int i = 2; i < V.size(); i++) {
        if(V[V[i].link].len%2) evenlink[i] = evenlink[V[i].link];
        else evenlink[i] = V[i].link;
    }
    // cout << evenlink;
    int tmp = tree.roots.back(), ans = 0;
    if(V[tmp].len%2) tmp = evenlink[tmp];
    while(tmp > 1) {
        int tmq = tree.roots[n-1-V[tmp].len];
        // cout << tmp << " " << tmq << endl;
        if(V[tmq].len%2) tmq = evenlink[tmq];
        ans = max(ans, (V[tmp].len+V[tmq].len)/2);
        tmp = evenlink[tmp];
    }
    cout << ans << "\n";
    return 0;
}
