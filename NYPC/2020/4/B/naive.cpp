#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<pl, int> pli;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pl> A(n);
    vector<pli> B(m);
    for(auto &i : A) cin >> i.fi >> i.se;
    for(int i = 0; i < m; i++) {
        cin >> B[i].fi.fi >> B[i].fi.se;
        B[i].se = i+1;
    }
    for(auto &i : A) {
        int minj = 0;
        for(int j = 1; j < m; j++)
            if((i.fi+B[j].fi.fi)*(i.se+B[minj].fi.se) > (i.se+B[j].fi.se)*(i.fi+B[minj].fi.fi)) minj = j;
        cout << minj+1 << "\n";
    }
    return 0;
}