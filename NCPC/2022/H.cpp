#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    vector<int> idx(n, -1), jdx(n, -1);
    for(int i = 0, j = 1; j < n; j++) {
        if(A[j] >= A[j-1]) idx[j] = i;
        else i = j;
    }
    for(int i = n-1, j = n-2; j >= 0; j--) {
        if(A[j] >= A[j+1]) jdx[j] = i;
        else i = j;
    }
    ll ans = 0LL;
    for(int i = 0; i < n; i++) {
        if(idx[i] >= 0 && jdx[i] >= 0)
            ans = max(ans, min(A[i]-A[idx[i]], A[i]-A[jdx[i]]));
    }
    cout << ans << "\n";
    return 0;
}
