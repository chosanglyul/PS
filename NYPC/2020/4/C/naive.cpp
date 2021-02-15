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

vector<ll> pre;

ll jag(int k, int s, int e, ll ma, ll mi) {
    if(k == 0) {
        //cout << s << " " << e << endl;
        if(s != e) return LLINF;
        return ma-mi;
    } else {
        ll ans = LLINF; 
        for(int i = s; i < e; i++) {
            ll siz = pre[i+1]-pre[s];
            ans = min(ans, jag(k-1, i+1, e, max(siz, ma), min(siz, mi)));
        }
        return ans;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k, x; cin >> n >> k >> x;
    if(n > 20) return 1;
    pre.resize(n+1);
    pre[0] = 0;
    cin >> pre[1];
    for(int i = 1; i < n; i++) {
        ll tmp; cin >> tmp;
        pre[i+1] = pre[i]+tmp;
    }
    cout << jag(k, 0, n, 0, LLINF) << endl;
    return 0;
}