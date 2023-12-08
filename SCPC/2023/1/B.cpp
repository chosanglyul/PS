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
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
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
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n, d; cin >> n >> d;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        sort(A.begin(), A.end());
        int ans = 0;
        int i, j;

        j = lower_bound(A.begin(), A.end(), 0) - A.begin();
        for(i = 0; i < n && A[i] <= 0; i++) {
            if(-A[i] > d) continue;
            while(j < n && -2LL*A[i]+A[j] <= d) j++;
            ans = max(ans, j-i);
        }
        while(j < n && A[j] <= d) j++;
        i = lower_bound(A.begin(), A.end(), 0) - A.begin();
        ans = max(ans, j-i);

        j = upper_bound(A.begin(), A.end(), 0) - A.begin(); j--;
        for(i = n-1; i >= 0 && A[i] >= 0; i--) {
            if(A[i] > d) continue;
            while(j >= 0 && 2LL*A[i]-A[j] <= d) j--;
            ans = max(ans, i-j);
        }
        while(j >= 0 && -A[j] <= d) j--;
        i = upper_bound(A.begin(), A.end(), 0) - A.begin(); i--;
        ans = max(ans, i-j);

        cout << ans;
        cout << endl;
    }
    return 0;
}
