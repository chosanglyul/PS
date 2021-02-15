#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
#define fi first
#define se second
const ll INF = 2e9+1;
const ll LLINF = 8e18+1;

vector<pl> E;

ll gety(pl x, ll t) { return x.fi*t+x.se; }
void rev() {
    for(auto &i : E) { i.fi *= -1; i.se *= -1; }
}

pl findcut(ll (*getvalue)(ll), ll y) {
    ll l = 0LL, r = INF;
    while(r-l >= 3) {
        ll p = (l*2 + r)/3, q = (l + r*2)/3;
        if(getvalue(p) <= getvalue(q)) {
            r = q;
        } else {
            l = p;
        }
    }
    ll res = LLINF, t;
    for(ll i = l; i <= r; i++) {
        if(res > getvalue(i)) {
            res = getvalue(i);
            t = i;
        }
    }
    if(res > y) return {-1LL, -1LL};
    pl ans = {0, 0};
    l = 0LL, r = t;
    while(l+1 < r) {
        ll mi = l+r >> 1;
        if(getvalue(mi) > y) l = mi;
        else r = mi;
    }
    for(ll i = l; i <= r; i++) {
        //cout << i << "   " << getvalue(i) << endl;
        if(y >= getvalue(i)) {
            ans.fi = i;
            break;
        }
    }
    l = t, r = INF;
    while(l+1 < r) {
        ll mi = l+r >> 1;
        if(getvalue(mi) > y) r = mi;
        else l = mi;
    }
    for(ll i = l; i <= r; i++) {
        if(y >= getvalue(i)) {
            ans.se = i;
        }
    }
    return ans;
}

ll getmin(ll t) {
    ll mi = LLINF;
    for(auto &i : E) mi = min(mi, gety(i, t));
    return mi;
}

ll getmax(ll t) {
    ll ma = -LLINF;
    for(auto &i : E) ma = max(ma, gety(i, t));
    return ma;
}

ll getcha(ll t) { return getmax(t)-getmin(t); }

pl gyo(pl a, pl b) {
    if(a.fi > b.se || a.se < b.fi) return {-1, -1};
    return {max(a.fi, b.fi), min(a.se, b.se)};
}
void print(pl a) { cout << a.fi << " " << a.se << endl; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll x, r, n; cin >> x >> r >> n;
    E.resize(n);
    for(auto &i : E) cin >> i.se >> i.fi;
    pl a = findcut(getcha, r);
    pl b = findcut(getmax, r+x);
    rev();
    pl c = findcut(getmax, 0LL);
    //print(a); print(b); print(c);
    pl lst = gyo(c, gyo(a, b));
    //print(lst);
    if(lst.fi < 0) cout << "F\n";
    else cout << "T\n";
    return 0;
}