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
const int P = 1e9+7;
const ll LLINF = 1e18+1;

bool cmp(pl a, pl b) {
    if(a.fi == b.fi) return a.se < b.se;
    return a.fi > b.fi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<pl> A(n);
        for(auto &i : A) cin >> i.fi;
        for(auto &i : A) cin >> i.se;
        sort(A.begin(), A.end(), cmp);
        ll tmp = 0; int i = 0;
        for(; i < A.size(); i++) {
            if(A[i].fi < tmp+A[i].se) break;
            else tmp += A[i].se;
        }
        if(i == A.size()) cout << tmp << "\n";
        else cout << max(tmp, A[i].fi) << "\n";
    }
    return 0;
}