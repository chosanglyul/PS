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

class Trie {
    private:
    struct Node {
        bool end;
        string s;
        map<string, int> nxt;
        int getNext(string &s) {
            auto iter = nxt.find(s);
            if(iter == nxt.end()) return -1;
            else return iter->se;
        }
        Node(string &s) {
            end = false;
            this->s = s;
        }
    };

    vector<Node> trie;
    
    void traverse(int idx, int depth) {
        if(depth >= 0) {
            for(int i = 0; i < depth; i++) cout << "--";
            cout << trie[idx].s << "\n";
        }
        for(auto &[s, jdx] : trie[idx].nxt) {
            if(jdx < 0) continue;
            traverse(jdx, depth+1);
        }
    }

    public:
    Trie() {
        string s;
        trie.resize(1, Node(s));
    }

    void insert(vector<string> &s) {
        int idx = 0;
        for(int i = 0; i < (int)s.size(); i++) {
            int jdx = trie[idx].getNext(s[i]);
            if(jdx == -1) {
                jdx = trie.size();
                trie.push_back(Node(s[i]));
                trie[idx].nxt.insert({s[i], jdx});
            }
            idx = jdx;
        }
        trie[idx].end = true;
    }

    void traverse() {
        traverse(0, -1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    Trie trie;
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        vector<string> A(t); cin >> A;
        trie.insert(A);
    }
    trie.traverse();
    return 0;
}