#include "jelly.h"
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

int find_maximum_unique(int x, int y, vector<int> a, vector<int> b) {
	vector<pii> M(a.size());
	for(int i = 0; i < M.size(); i++) M[i] = {a[i], b[i]};
	sort(M.begin(), M.end());
	vector<vector<int>> dp(M.size()+1, vector<int>(x+1, INF));
	fill(dp[0].begin(), dp[0].end(), 0);
	for(int i = 0; i < M.size(); i++) {
		for(int j = 0; j <= x; j++) {
			dp[i+1][j] = dp[i][j]+M[i].se;
			if(j >= M[i].fi) dp[i+1][j] = min(dp[i+1][j], dp[i][j-M[i].fi]);
		}
	}
	//cout << M;
	//cout << " " << dp;
	int ans = 0;
	for(int i = 0; i <= M.size(); i++) {
		int tmp = y-(*min_element(dp[i].begin(), dp[i].end()));
		if(tmp < 0) continue;
		int cnt = i;
		vector<int> T;
		for(int j = i; j < M.size(); j++) T.push_back(M[j].se);
		sort(T.begin(), T.end(), greater<int>());
		//cout << i << " " << tmp << "\n" << T;
		while(T.size() && T.back() <= tmp) {
			tmp -= T.back();
			T.pop_back();
			cnt++;
		}
		//cout << cnt << "\n\n";
		ans = max(ans, cnt);
	}
	return ans;
}
