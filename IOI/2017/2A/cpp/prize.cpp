#include "prize.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }

pii query(int i) {
	static vector<pii> M = vector<pii>(202020, {-1, -1});
	if(M[i].fi < 0 && M[i].se < 0) {
		vector<int> res = ask(i);
		return M[i] = {res[0], res[1]};
	} else return M[i];
}

bool validate(int x, int s, int e, int ma, int &mi, pii &qmi, vector<pii> &R) {
	if(x >= e || x < s) return false;
	pii tmp = query(x);
	if(tmp.fi+tmp.se != ma) {
		R.push_back({x, tmp.fi+tmp.se});
		return false;
	} else {
		mi = x; qmi = tmp;
		return true;
	}
}

vector<pii> solve(int s, int e, int cnt, int lcnt, int rcnt, int ma) {
	//cout << s << " " << e << " " << cnt << " " << lcnt << " " << rcnt << " " << ma << "\n";
	if(cnt == 0) return vector<pii>();
	vector<pii> ret;
	int cl = s+e>>1, cr = s+e>>1;
	pii qmi; int mi;
	while(true) {
		if(validate(cr, s, e, ma, mi, qmi, ret)) break;
		else cr++;
  		if(validate(cl-1, s, e, ma, mi, qmi, ret)) break;
		else cl--;
		if(cl < s && cr >= e) return ret;
	}
	qmi.fi -= lcnt, qmi.se -= rcnt;
	if(cr == mi) qmi.fi -= cr-cl;
	else qmi.se -= cr-cl;
	//cout << mi << " " << cl << " " << cr << "  " << qmi << "\n";
	vector<pii> L = solve(s, cl, qmi.fi, lcnt, rcnt+cr-cl+qmi.se, ma);
	vector<pii> R = solve(cr, e, qmi.se, lcnt+cr-cl+qmi.fi, rcnt, ma);
	for(auto i : L) ret.push_back(i);
	for(auto i : R) ret.push_back(i);
	return ret;
}

int find_best(int n) {
	int sq = (sqrt(n)+1)*2;
	vector<int> X;
	for(int i = 0; i <= n/sq; i++) X.push_back(sq*i);
	if(X.back() != n) X.push_back(n);
	//cout << X;
	vector<int> Y(X);
	int ma = 0;
	vector<pii> Q, LR;
	for(int i = 0; i+1 < X.size(); i++) {
		pii tmp = query(X[i]);
		Q.push_back(tmp);
		LR.push_back({X[i], X[i]});
		ma = max(tmp.fi+tmp.se, ma);
	}
	for(int i = 0; i+1 < X.size(); i++) {
		for(int j = 1; j < 4; j++) {
			int x = X[i]+sq/4*j;
			if(x >= n) continue;
			pii tmp = query(x);
			ma = max(tmp.fi+tmp.se, ma);
		}
	}
	//cout << ma << "\n";
	//cout << Q;
	vector<pii> ans;
	for(int i = 0; i+1 < X.size(); i++) {
		if(Q[i].fi+Q[i].se != ma) {
			ans.push_back({X[i], Q[i].fi+Q[i].se});
			int s = (i == 0 ? 0 : Y[i-1]), e = Y[i+1];
			while(LR[i].fi >= s && LR[i].se < e) {
				if(validate(LR[i].se, s, e, ma, X[i], Q[i], ans)) break;
				else LR[i].se++;
  				if(validate(LR[i].fi-1, s, e, ma, X[i], Q[i], ans)) break;
				else LR[i].fi--;
			}
			LR[i].fi = max(s, LR[i].fi);
			LR[i].se = min(e, LR[i].se);
		}
	}
	Q.push_back({ma, 0});
	LR.push_back({n, n});
	//cout << ans;
	//cout << LR;
	for(int i = 1; i < Q.size(); i++) {
		int lcnt = Q[i-1].fi, rcnt = Q[i].se;
		if(X[i-1] != LR[i-1].se) lcnt += LR[i-1].se-LR[i-1].fi;
		if(X[i] == LR[i].se) rcnt += LR[i].se-LR[i].fi;
		//cout << LR[i-1].se << " " << LR[i].fi << " " << lcnt << " " << rcnt << "\n";
		vector<pii> tmp = solve(LR[i-1].se, LR[i].fi, ma-lcnt-rcnt, lcnt, rcnt, ma);
		for(auto i : tmp) ans.push_back(i);
	}
	for(auto i : ans) if(i.se == 0) return i.fi;
	exit(EXIT_FAILURE);
}
