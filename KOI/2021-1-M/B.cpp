#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll LLINF = (ll)1e18;
#define fi first
#define se second

vector<int> A, R;
vector<ll> B, C, D;
vector<vector<int>> E;

void dfs(int x) {
    B[x] = A[x];
    C[x] = D[x] = -LLINF;
    vector<ll> V;
    for(auto i : E[x]) {
        dfs(i);
        if(B[i] > 0LL) {
            B[x] += B[i];
            V.push_back(C[i]);
            C[x] = max(C[x], C[i]);
            D[x] = max(D[x], D[i]);
        } else R.push_back(i);
    }
    C[x] = max(C[x], B[x]);
    if(V.size() > 1) {
        sort(V.begin(), V.end(), [&](ll a, ll b) { return a > b; });
        D[x] = max(D[x], V[0]+V[1]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; E.resize(n);
    B.resize(n); C.resize(n); D.resize(n);
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        A.push_back(x);
        E[--y].push_back(i);
    }
    dfs(0); R.push_back(0);
    sort(R.begin(), R.end(), [&](int a, int b) { return C[a] > C[b]; });
    ll ans = ((R.size() > 1) ? C[R[0]]+C[R[1]] : -LLINF);
    for(auto i : R) ans = max(ans, D[i]);
    cout << ans << "\n";
    return 0;
}