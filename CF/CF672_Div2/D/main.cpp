#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
#define fi first
#define se second
const ll P = 998244353;
const ll LLINF = 1e18+1;

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

ll A[303030], B[303030];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    A[0] = 1;
    for(ll i = 1; i < 303030; i++)
        A[i] = (A[i-1]*i)%P;
    B[303029] = inv(A[303029], P);
    for(ll i = 303029; i >= 1; i--)
        B[i-1] = (B[i]*i)%P;
    int n, k; cin >> n >> k;
    ll ans = 0;
    vector<pi> C(n);
    vector<pii> D;
    for(int i = 0; i < n; i++) {
        cin >> C[i].fi >> C[i].se;
        D.push_back({C[i].fi, {-1, C[i].se}});
        D.push_back({C[i].se, {1, C[i].fi}});
    }
    sort(D.begin(), D.end());
    priority_queue<int, vector<int>, greater<int>> Q;
    for(int i = 0; i < D.size(); i++) {
        //cout << i << " " << D[i].fi << " " << D[i].se.fi << " " << D[i].se.se << endl;
        if(D[i].se.fi == -1) Q.push(D[i].se.se);
        else if(Q.size()) {
            int tmp = Q.top();
            int siz = Q.size();
            Q.pop();
            while(Q.size() && Q.top() == tmp) { Q.pop(); i++; }
            if(siz >= k) {
                //cout << siz << " " << Q.size() << " " << k << "\n";
                //cout << A[siz] << " " << B[k] << " " << B[siz-k] << "\n";
                ll ncr = (((A[siz]*B[k])%P)*B[siz-k])%P;
                if(Q.size() >= k) ncr = mod(ncr-(((A[Q.size()]*B[k])%P)*B[Q.size()-k])%P, P);
                ans = mod(ans+ncr, P);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}