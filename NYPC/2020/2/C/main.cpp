#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const ll LLINF = 1e10+1;

ll gety(pl x, ll t) { return x.fi*t+x.se; }
void rev(vector<pl>& E) {
    for(auto &i : E) { i.fi *= -1; i.se *= -1; }
}
ll findx(pl a, pl b) { 
    if(b.fi == a.fi) return LLINF;
    else return (a.se-b.se)/(b.fi-a.fi);
}

vector<pll> mkcv(vector<pl>& E) {
    vector<pll> ans;
    ans.emplace_back(0, 0, LLINF);
    for(int i = 0; i < E.size(); i++) {
        if(E[ans.back().fi].se >= E[i].se) continue;
        int l = 0, r = ans.size();
        while(l+1 < r) {
            int mi = l+r>>1;
            pl mid = E[ans[mi].fi];
            ll x = findx(E[i], mid);
            if(x >= mid.fi) l = mi;
            else r = mi;
        }
        ll x = findx(E[i], E[l]);
        while(ans.back().se.se <= x) ans.pop_back();
        ans[ans.size()-1].se.fi = x+1;
        ans.emplace_back(i, 0, x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int x, r, n; cin >> x >> r >> n;
    vector<pl> E(n);
    for(auto &i : E) cin >> i.se >> i.fi;
    sort(E.begin(), E.end());
    vector<pll> ma = mkcv(E);
    rev(E); reverse(E.begin(), E.end());
    vector<pll> mi = mkcv(E);
    rev(E);
    return 0;
}