#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

bool chk(pl a, pll b) { return abs(a.fi-b.se.fi)+abs(b.se.se) <= a.se; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    if(n > 2) return 1;
    vector<pl> A(n);
    vector<pll> B(m);
    for(auto &i : A) cin >> i.fi >> i.se;
    for(auto &i : B) cin >> i.se.fi >> i.se.se >> i.fi;
    if(n == 2) {
        ll oa = 0, ob = 0, al = 0;
        for(int i = 0; i < m; i++) {
            if(chk(A[0], B[i])) {
                if(chk(A[1], B[i])) al += B[i].fi;
                else oa += B[i].fi;
            } else ob += B[i].fi;
        }
        if(ob > oa+al) cout << ob << endl;
        else if(oa > ob+al) cout << oa << endl;
        else cout << (oa+ob+al+1)/2 << endl;
    } else {
        ll al = 0;
        for(auto &i : B) al += i.fi;
        cout << al << endl;
    }
    return 0;
}