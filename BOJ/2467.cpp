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
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    sort(A.begin(), A.end());
    pi mini = {-1, -1};
    int minval = 2*INF;
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(A.begin(), A.end(), -A[i])-A.begin();
        for(int j = idx-2; j <= idx+2; j++) {
            if(j < 0 || j >= n || j == i) continue;
            if(abs(A[j]+A[i]) < minval) {
                minval = abs(A[j]+A[i]);
                if(A[i] > A[j]) mini = {j, i};
                else mini = {i, j};
            }
        }
    }
    cout << A[mini.fi] << " " << A[mini.se] << endl;
    return 0;
}