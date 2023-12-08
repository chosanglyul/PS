#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll P = 998244353LL;

ll solve(int l, int r, int s, int e, vector<int> &A, vector<int> &B, vector<int> &T) {
    // cout << l << " " << r << " " << s << " " << e << "\n";
    if(T[A[l]] != e-1) return 0LL;
    if(s+1 == e) return 1LL;
    ll ans = 1LL;
    int mi = T[A[l+1]];
    if(mi < s || mi >= e) return 0LL;
    int len = mi-s+1;
    if(len > 0) ans = (ans*solve(l+1, l+1+len, s, s+len, A, B, T))%P;
    if(len < e-s-1) ans = (ans*solve(l+1+len, r, s+len, e-1, A, B, T))%P;
    if(len == 0 || len == e-s-1) ans = (ans*2LL)%P;
    // cout << l << " " << r << " " << s << " " << e << " " << ans << "\n";
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n), B(n), T(n);
    for(auto &i : A) { cin >> i; i--; }
    for(auto &i : B) { cin >> i; i--; }
    for(int i = 0; i < n; i++) T[B[i]] = i;
    cout << solve(0, n, 0, n, A, B, T) << "\n";
    return 0;
}
