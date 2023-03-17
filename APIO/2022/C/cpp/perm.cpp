#include "perm.h"
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
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }

vector<int> construct_permutation(ll k) {
	vector<int> chk;
	for(int i = 0; k; i++, k >>= 1)
		if(k&1) chk.push_back(i);
	vector<int> ret;
	int ma = chk.back(); chk.pop_back();
	for(int i = 0; i < ma; i++) ret.push_back(i*2+1);
	reverse(chk.begin(), chk.end());
	for(auto i : chk) ret.push_back(i*2);
	for(int i = ma+2; i+1 < ret.size(); i++) {
		if(ret[i]-2 == ret[i+1]) {
			ret.erase(ret.begin()+i);
			swap(ret[i-1], ret[i]);
			swap(ret[i-2], ret[i-1]);
		}
	}
	vector<int> srt(ret);
	sort(srt.begin(), srt.end());
	for(auto &i : ret) i = lower_bound(srt.begin(), srt.end(), i) - srt.begin();
	return ret;
}