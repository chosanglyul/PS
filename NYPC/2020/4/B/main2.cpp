#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<pl, int> pli;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

ll ccw(pl a, pl b, pl c) { return a.fi*b.se + b.fi*c.se + c.fi*a.se - a.se*b.fi - b.se*c.fi - c.se*a.fi; }
ll dist(pl a, pl b) { return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pl> A(n);
    vector<pli> K(m), B, hull;
    for(auto &i : A) cin >> i.fi >> i.se;
    for(int i = 0; i < m; i++) {
        cin >> K[i].fi.fi >> K[i].fi.se;
        K[i].se = i+1;
    }
    sort(K.begin(), K.end());
    B.push_back(K[0]);
    for(int i = 1; i < m; i++)
        if(K[i].fi != B.back().fi) B.push_back(K[i]);
    sort(B.begin()+1, B.end(), [&](pli a, pli b){
		ll cw = ccw(B[0].fi, a.fi, b.fi);
		if(cw) return cw > 0;
		return dist(B[0].fi, a.fi) < dist(B[0].fi, b.fi);
	});
    for(auto &i : B) {
        while(hull.size() >= 2 && ccw(hull[hull.size()-2].fi, hull.back().fi, i.fi) < 0) hull.pop_back();
        hull.push_back(i);
    }
    sort(hull.begin(), hull.end(), [&](pli a, pli b) { return a.se < b.se; });
    for(auto &i : A) {
        int minj = 0;
        for(int j = 1; j < hull.size(); j++)
            if((i.fi+hull[j].fi.fi)*(i.se+hull[minj].fi.se) > (i.se+hull[j].fi.se)*(i.fi+hull[minj].fi.fi)) minj = j;
        cout << hull[minj].se << "\n";
    }
    return 0;
}