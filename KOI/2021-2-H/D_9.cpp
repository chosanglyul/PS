#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<pi, int> pii;
#define fi first
#define se second

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y); E[y].push_back(x);
    }
    vector<pii> A(m);
    for(auto &i : A) cin >> i.fi.fi >> i.fi.se >> i.se;
    sort(A.begin(), A.end(), [&](pii a, pii b) {
        if(a.fi.fi+a.fi.se == b.fi.fi+b.fi.se)
            return a.fi.fi-a.fi.se < b.fi.fi-b.fi.se;
        return a.fi.fi+a.fi.se < b.fi.fi+b.fi.se;
    });
    vector<ll> B(m+1, 0LL);
    vector<int> C;
    ll ans = 0LL;
    for(auto &i : A) C.push_back(i.fi.fi+i.fi.se);
    //for(auto i : C) cout << i << " ";
    //cout << "\n";
    for(int i = 0; i < m; i++) {
        auto iter = lower_bound(C.begin(), C.end(), A[i].fi.fi-A[i].fi.se);
        int idx = iter-C.begin();
        B[i+1] = max(B[i], B[idx]+A[i].se);
        //cout << B[i+1] << " ";
        ans = max(B[i+1], ans);
    }
    cout << ans << "\n";
	return 0;
}
