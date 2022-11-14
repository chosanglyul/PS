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

struct Node {
    Node *go[26], *fail;
    bool end;
    Node() : fail(nullptr), end(false) { fill(go, go + 26, nullptr); }
    ~Node() {
        for (Node *next: go)
            if (next) delete next;
    }
};

Node * build_trie(vector<string> &patterns) {
    Node *root = new Node();

    for (string &p: patterns) {
        Node *curr = root;
        for (char c: p) {
            if (!curr->go[c - 'a']) curr->go[c - 'a'] = new Node();
            curr = curr->go[c - 'a'];
        }
        curr->end = true;
    }

    queue<Node *> q; q.push(root);
    root->fail = root;

    while (!q.empty()) {
        Node *curr = q.front(); q.pop();
        for (int i = 0; i < 26; i++) {
            Node *next = curr->go[i];
            if (!next) continue;
            q.push(next);

            if (curr == root) next->fail = root;
            else {
                Node *dest = curr->fail;
                while (dest != root && !dest->go[i]) dest = dest->fail;
                if (dest->go[i]) dest = dest->go[i];
                next->fail = dest;
                next->end |= dest->end;
            }
        }
    }

    return root;
}

bool find_trie(Node *trie, string &s) {
    Node *curr = trie;
    for (char c: s) {
        while (curr != trie && !curr->go[c - 'a']) curr = curr->fail;
        if (curr->go[c - 'a']) curr = curr->go[c - 'a'];
        if (curr->end) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<string> S(n);
    for(auto &i : S) cin >> i;
    Node* root = build_trie(S);
    int q; cin >> q;
    while(q--) {
        string s; cin >> s;
        cout << (find_trie(root, s) ? "YES" : "NO") << "\n";
    }
    return 0;
}