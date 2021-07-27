#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
typedef pair<int, char> pic;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        vector<int> C(26, 0);
        vector<pic> A;
        int x = -1;
        for(auto &i : s) C[i-'a']++;
        for(int i = 0; i < C.size(); i++) {
            if(C[i]) {
                if(C[i] == 1 && x == -1) x = A.size();
                A.emplace_back(C[i], 'a'+i);
            }
        }
        if(A.size() == 1) {
            cout << s << "\n";
        } else if(x > -1) {
            cout << A[x].se; A[x].fi--;
            for(int i = 0; i < A.size(); i++)
                for(int j = 0; j < A[i].fi; j++)
                    cout << A[i].se;
            cout << "\n";
        } else if(A[0].fi > (s.size()/2+1)) {
            cout << A[0].se; A[0].fi--;
            cout << A[1].se; A[1].fi--;
            if(A.size() == 2) {
                for(int i = 0; i < A[1].fi; i++) cout << A[1].se;
                for(int i = 0; i < A[0].fi; i++) cout << A[0].se;
            } else {
                for(int i = 0; i < A[0].fi; i++) cout << A[0].se;
                cout << A[2].se; A[2].fi--;
                for(int i = 1; i < A.size(); i++)
                    for(int j = 0; j < A[i].fi; j++)
                        cout << A[i].se;
            }
            cout << "\n";
        } else {
            cout << A[0].se; A[0].fi--;
            for(int i = 1; i < A.size(); ) {
                if(A[0].fi) {
                    cout << A[0].se;
                    A[0].fi--;
                }
                cout << A[i].se;
                if(--A[i].fi == 0) i++;
            }
            if(A[0].fi) cout << A[0].se;
            cout << "\n";
        }
    }
    return 0;
}