#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<pl, int> pli;
typedef pair<pl, pi> plpi;
#define fi first
#define se second

ll ccw(pl a, pl b, pl c) { return a.fi*b.se + b.fi*c.se + c.fi*a.se - a.se*b.fi - b.se*c.fi - c.se*a.fi; }
ll dist(pl a, pl b) { return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pl> A(n);
    vector<pli> K(m), B;
    vector<plpi> hull, H;
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
		int cw = ccw(B[0].fi, a.fi, b.fi);
		if(cw) return cw > 0;
		return dist(B[0].fi, a.fi) < dist(B[0].fi, b.fi);
	});
	for(auto &i : B) {
		while(H.size() >= 2 && ccw(H[H.size()-2].fi, H.back().fi, i.fi) < 0) H.pop_back();
		H.push_back({i.fi, {i.se, i.se}});
	}
    for(auto &i : H) {
        while(hull.size() >= 2 && ccw(hull[hull.size()-2].fi, hull.back().fi, i.fi) == 0) {
            hull[hull.size()-2].se.se = min(hull[hull.size()-2].se.se, hull.back().se.fi);
            hull.pop_back();
        }
        hull.push_back(i);
    }
    hull.push_back(hull[0]);
    for(int i = 0; i < hull.size()-1; i++) hull[i].se.se = min(hull[i].se.se, hull[i+1].se.fi);
    for(int i = 0; i < hull.size()-1; i++) {
        if(hull[i].fi.fi >= hull[i+1].fi.fi) hull.erase(hull.begin()+i+1, hull.end());
    }
    for(auto &i : A) {
        i.fi *= -1; i.se *= -1;
        bool ok = false;
        for(int j = 0; j < hull.size()-1; j++) {
            ll tmp = ccw(i, hull[j].fi, hull[j+1].fi);
            if(tmp > 0) {
                cout << hull[j].se.fi << "\n";
                ok = true;
                break;
            } else if(tmp == 0) {
                cout << hull[j].se.se << "\n";
                ok = true;
                break;
            }
        }
        if(!ok) cout << hull.back().se.fi;
    }
    return 0;
}