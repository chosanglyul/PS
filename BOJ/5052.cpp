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

struct Trie {
    bool ter = false;
    const int N_ALPHA = 10;
    const char S_ALPHA = '0';
    vector<Trie*> next = vector<Trie*>(N_ALPHA, nullptr);

    ~Trie() {
        for(auto i : next)
            if(i) delete i;
    }

    int nextidx(const char* key) { return *key - S_ALPHA; }

    void insert(const char* key) {
        if(*key == 0) ter = true;
        else {
            if(!next[nextidx(key)])
                next[nextidx(key)] = new Trie();
            next[nextidx(key)]->insert(key+1);
        }
    }

    bool find(const char* key) {
        if(*key == 0 && ter) return true;
        else if(!next[nextidx(key)]) return false;
        else return next[nextidx(key)]->find(key+1);
    }

    bool pre_find(const char* key) {
        if(*key == 0) return true;
        else if(!next[nextidx(key)]) return false;
        else return next[nextidx(key)]->pre_find(key+1);
    }

    bool suf_find(const char* key) {
        if(ter) return true;
        else if(*key == 0 || !next[nextidx(key)]) return false;
        else return next[nextidx(key)]->suf_find(key+1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        Trie* root = new Trie();
        int n; cin >> n;
        vector<string> S(n);
        for(auto &i : S) cin >> i;
        bool can = true;
        for(auto &i : S) {
            if(root->pre_find(i.c_str()) || root->suf_find(i.c_str())) {
                can = false;
                break;
            }
            root->insert(i.c_str());
        }
        cout << (can?"YES\n":"NO\n");
    }
    return 0;
}