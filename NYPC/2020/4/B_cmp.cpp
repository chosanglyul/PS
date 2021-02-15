#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<pl, int> pli;
typedef pair<pl, pi> plpi;
#define fi first
#define se second

vector<int> naive(vector<pl>& A, vector<pli>& B, int n, int m) {
    vector<int> ans;
    for(auto &i : A) {
        int minj = 0;
        for(int j = 1; j < m; j++)
            if((i.fi+B[j].fi.fi)*(i.se+B[minj].fi.se) > (i.se+B[j].fi.se)*(i.fi+B[minj].fi.fi)) minj = j;
        ans.push_back(minj+1);
    }
    return ans;
}

ll ccw(pl a, pl b, pl c) { return a.fi*b.se + b.fi*c.se + c.fi*a.se - a.se*b.fi - b.se*c.fi - c.se*a.fi; }
ll dist(pl a, pl b) { return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se); }

vector<plpi> hull;

vector<int> sol(vector<pl> A, vector<pli> K, int n, int m, bool wrong) {
    vector<pli> B;
    sort(K.begin(), K.end());
    B.push_back(K[0]);
    for(int i = 1; i < m; i++)
        if(K[i].fi != B.back().fi) B.push_back(K[i]);
	sort(B.begin()+1, B.end(), [&](pli a, pli b){
		int cw = ccw(B[0].fi, a.fi, b.fi);
		if(cw) return cw > 0;
		return dist(B[0].fi, a.fi) < dist(B[0].fi, b.fi);
	});
    vector<plpi> H;
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
    if(wrong) {
        cout << endl << hull.size() << endl;
        for(auto &i : hull) cout << i.fi.fi << " " << i.fi.se << " " << i.se.fi << " " << i.se.se << endl;
        cout << endl;
    }
    for(int i = 0; i < hull.size()-1; i++) hull[i].se.se = min(hull[i].se.se, hull[i+1].se.fi);
    for(int i = 0; i < hull.size()-1; i++) if(hull[i].fi.fi >= hull[i+1].fi.fi) hull.erase(hull.begin()+i+1, hull.end());

    vector<int> ans;
    for(auto &i : A) {
        i.fi *= -1; i.se *= -1;
        bool ok = false;
        for(int j = 0; j < hull.size()-1; j++) {
            ll tmp = ccw(i, hull[j].fi, hull[j+1].fi);
            if(wrong) cout << j << "   " << tmp << "   " << hull[j].se.fi << " " << hull[j].se.se << endl;
            if(tmp > 0) {
                ans.push_back(hull[j].se.fi);
                if(wrong) {
                    cout << hull[j].se.fi << endl;
                    cout << i.fi << " " << i.se << " " << hull[j].fi.fi << " " << hull[j].fi.se << " " << hull[j+1].fi.fi << " " << hull[j+1].fi.se << endl;
                }
                ok = true;
                break;
            } else if(tmp == 0) {
                ans.push_back(hull[j].se.se);
                if(wrong) {
                    cout << hull[j].se.se << endl;
                    cout << i.fi << " " << i.se << " " << hull[j].fi.fi << " " << hull[j].fi.se << " " << hull[j+1].fi.fi << " " << hull[j+1].fi.se << endl;
                }
                ok = true;
                break;
            }
        }
        if(!ok) ans.push_back(hull.back().se.fi);
    }
    return ans;
}

int main() {
    srand((unsigned int)time(NULL));
    int N, M, k; cin >> N >> M >> k;
    int tt = 0;
    while(1) {
        hull.clear();
        int n = (rand()%N)+1;
        int m = (rand()%M)+1;
        vector<pl> A(n);
        vector<pli> B(m);
        vector<int> N(n), S(n);
        for(auto &i : A) {
            i.fi = (rand()%k)+1;
            i.se = (rand()%k)+1;
        }
        for(int i = 0; i < m; i++) {
            B[i].fi.fi = (rand()%k)+1;
            B[i].fi.se = (rand()%k)+1;
            B[i].se = i+1;
        }
        N = naive(A, B, n, m);
        S = sol(A, B, n, m, false);
        if(N != S) {
            cout << n << " " << m << endl;
            for(auto &i : A) cout << i.fi << " " << i.se << endl << endl;
            for(auto &i : B) cout << i.fi.fi << " " << i.fi.se << endl << endl;
            for(auto &i : N) cout << i << " ";
            cout << endl;
            for(auto &i : S) cout << i << " ";
            cout << endl << endl;
            hull.clear();
            S = sol(A, B, n, m, true);
            break;
        }
        cout << ++tt << endl;
    }
}