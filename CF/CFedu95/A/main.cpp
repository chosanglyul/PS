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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        ll x, y, k; cin >> x >> y >> k;
        ll tmp = k*(y+1)-1;
        --x;
        if(tmp%x) cout << tmp/x+1+k << "\n";
        else cout << tmp/x+k << "\n";
    }
    return 0;
}