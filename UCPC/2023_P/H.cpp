#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define eb emplace_back
#define all(v) (v).begin(),(v).end()

const ll INF = 1e18;

vector<ll> f;

ll cal(ll N) {
    if(N <= 3) return N;
    int k = lower_bound(all(f), N) - f.begin();
    if(f[k] == N) {
        ll ak = cal(k);
        if(ak == -1 || ak >= f.size()) return -1;
        return f[ak];
    }
    k--;
    if((N - k) % 2) {
        if(k < f.size() - 1 && f[k + 1] == N + 1) return N + 2;
        else return N + 1;
    }
    else {
        int c;
        if(f[k] == N - 1) c = N - 2;
        else c = N - 1;
        if(c >= f.size()) return -1;
        return f[c];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll T, N;

    f.eb(0ll);
    f.eb(1ll);
    f.eb(2ll);
    while(true) {
        ll t = f[f.size() - 2] + f.back();
        if(t < INF) f.eb(t);
        else break;
    }

    cin >> T;
    while(T--) {
        cin >> N;
        cout << cal(N) << "\n";
    }
    return 0;
}