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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    vector<vector<int>> V(n);
    vector<set<int>> S(n);
    vector<pi> A(k);
    vector<int> B(n), C(n, -1);
    for(int i = 0; i < n; i++) {
        V[i].push_back(i);
        B[i] = i;
    }
    for(auto &i : A) {
        cin >> i.fi >> i.se; --i.fi, --i.se;
        V[B[i.se]].push_back(i.fi);
        V[B[i.fi]].push_back(i.se);
        swap(B[i.fi], B[i.se]);
    }
    for(int i = 0; i < n; i++) {
        if(C[i] != -1) continue;
        int tmp = i;
        do {
            C[tmp] = i;
            for(auto j : V[tmp]) S[i].insert(j);
            tmp = B[tmp];
        } while(tmp != i);
    }
    for(int i = 0; i < n; i++)
        cout << S[C[i]].size() << "\n";
    return 0;
}