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

struct Node {
    bool end;
    map<char, int> nxt;
    
    Node() {
        end = false;
    }
    
    int get(char c) {
        auto iter = nxt.find(c);
        if(iter == nxt.end()) return -1;
        else return iter->se;
    }
    void set(char c, int idx) { nxt.insert({c, idx}); }
};

class Trie {
    private:
    vector<Node> trie;

    public:
    Trie() { trie.resize(1, Node()); }

    int size() { return trie.size(); }
    int get(int idx, char c) { return trie[idx].get(c); }
    void set(int idx, char c, int jdx) { trie[idx].set(c, jdx); }
    bool getEnd(int idx) { return trie[idx].end; }
    void setEnd(int idx) { trie[idx].end = true; }
    
    void insert(vector<char> &s) {
        int idx = 0;
        for(auto c : s) {
            int jdx = get(idx, c);
            if(jdx == -1) {
                jdx = trie.size();
                set(idx, c, jdx);
                trie.push_back(Node());
            }
            idx = jdx;
        }
        setEnd(idx);
    }
};

class AhoCorasick {
    private:
    Trie T;
    vector<int> fail, depth;

    public:
    AhoCorasick(Trie &T) {
        this->T = T;
        fail.resize(T.size(), 0);
        depth.resize(T.size(), 0);
        queue<int> Q; Q.push(0);
        while(Q.size()) {
            int idx = Q.front(); Q.pop();
            for(int c = 'a'; c <= 'z'; c++) {
                int jdx = T.get(idx, c);
                if(jdx == -1) continue;
                if(idx) {
                    int tmp = fail[idx];
                    while(tmp && T.get(tmp, c) == -1) tmp = fail[tmp];
                    if(T.get(tmp, c) != -1) tmp = T.get(tmp, c);
                    fail[jdx] = tmp;
                }
                if(T.getEnd(fail[jdx])) T.setEnd(jdx);
                depth[jdx] = depth[idx]+1;
                Q.push(jdx);
            }
        }
    }

    int match(vector<char> &s) {
        int idx = 0, cnt = 0, dep = 0;
        for(auto c : s) {
            while(idx && T.get(idx, c) == -1) {
                dep -= depth[idx]-depth[fail[idx]];
                dep = max(0, dep);
                idx = fail[idx];
            }
            if(T.get(idx, c) != -1) {
                idx = T.get(idx, c);
                dep++;
            }
            if(T.getEnd(idx)) {
                cnt += dep;
                dep = 0;
            }
        }
        return cnt;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<char> s(n); cin >> s;
    int m; cin >> m;
    while(m) {
        Trie trie;
        for(int i = 0; i < min(500, m); i++) {
            string t; cin >> t;
            vector<char> v(t.begin(), t.end());
            trie.insert(v);
        }
        AhoCorasick aho(trie);
        n -= aho.match(s);
        m -= min(500, m);
    }
    cout << n << "\n";
    return 0;
}