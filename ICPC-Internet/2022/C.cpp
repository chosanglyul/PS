#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

ll myabs(ll x) { return x > 0LL ? x : -x; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    sort(A.begin(), A.end());
    ll su = 0LL;
    for(auto i : A) su += i;
    ll tmp = su%n;
    su /= n;
    vector<ll> B(n, su);
    for(int i = 0; i < tmp; i++) B[i]++;
    reverse(B.begin(), B.end());
    ll ans = 0LL;
    for(int i = 0; i < n; i++) ans += myabs(A[i]-B[i]);
    cout << ans/2 << "\n";
    return 0;
}