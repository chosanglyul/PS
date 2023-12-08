#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<pll, int> plli;
typedef pair<pli, int> plii;
#define fi first
#define se second

const ll LLINF = (ll)1e18+5;
const ll P = 998244353LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string s; cin >> s;
    
    int top = 0, can = 1;
    for(int i = 0; i < 2*n; i++) {
        if(s[i] == '(') top++;
        else top--;
        if(top < 0) can = 0;
    }
    if(can) {
        ll ans = 1LL;
        for(int i = 0; i < 2*n; i++) ans = (ans*2LL)%P;
        cout << (ans-1LL+P)%P << "\n";
        return 0;
    }

    vector<vector<ll>> D(2*n+1, vector<ll>(n+1, 0LL)); D[0][0] = 1LL;
    for(int i = 1, cnt = 0; i <= 2*n; i++) {
        bool tmp = (s[i-1] == ')');
        cnt += tmp;
        for(int j = 0; j <= n; j++) {
            if(2*(cnt-j) > i) continue;
            D[i][j] += D[i-1][j];
            if(j && tmp) D[i][j] += D[i-1][j-1];
            else if(!tmp) D[i][j] += D[i-1][j];
            D[i][j] %= P;
        }
    }

    vector<vector<ll>> E(2*n+1, vector<ll>(n+1, 0LL)); E[2*n][0] = 1LL;
    for(int i = 2*n-1, cnt = 0; i >= 0; i--) {
        bool tmp = (s[i] == '(');
        cnt += tmp;
        for(int j = 0; j <= n; j++) {
            if(2*(cnt-j) > (2*n-i)) continue;
            E[i][j] += E[i+1][j];
            if(j && tmp) E[i][j] += E[i+1][j-1];
            else if(!tmp) E[i][j] += E[i+1][j];
            E[i][j] %= P;
        }
    }

    ll ans = 0LL;
    for(int i = 0; i < 2*n; i++) {
        for(int j = 1; j <= n; j++) {
            if(s[i] == ')') ans += D[i][j]*E[i+1][j];
            else if(E[i][j] && j) ans += D[i][j]*E[i+1][j-1];
            ans %= P;
        }
    }
    cout << ans << "\n";
    return 0;
}
