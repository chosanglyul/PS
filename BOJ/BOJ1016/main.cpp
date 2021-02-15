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

bool chk[1010101], oo[1010101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll a, b; cin >> a >> b;
    ll ans = b-a+1;
    for(ll i = 2; i*i <= b; i++) {
        if(chk[i]) continue;
        for(ll j = i; j*j <= b; j += i) chk[j] = true;
        for(ll tmp = ((a-1)/(i*i)+1)*i*i; tmp <= b; tmp += i*i)
            if(!oo[tmp-a]) oo[tmp-a] = true, ans--;
    }
    cout << ans << "\n";
    return 0;
}