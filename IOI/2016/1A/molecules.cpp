#include "molecules.h"
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

vector<int> find_subset(int l, int u, vector<int> w) {
    vector<vector<pii>> A(w.size()+1);
    A[0].push_back({l, u});
    for(int i = 1; i <= w.size(); i++) {
        A[i].push_back({A[i-1][0].fi, A[i-1][0].se});
        for(int j = 1; j < i; j++) {
            pii a = {A[i-1][j].fi, A[i-1][j].se};
            pii b = {A[i-1][j-1].fi-w[i-1], A[i-1][j-1].se-w[i-1]};
            A[i].push_back({min(a.fi, b.fi), max(a.se, b.se)});
        }
        A[i].push_back({A[i-1][i-1].fi-w[i-1], A[i-1][i-1].se-w[i-1]});
    }
    int idx = -1;
    for(int i = 0; i < A.back().size(); i++)
        if((ll)A.back()[i].fi*A.back()[i].se <= 0LL)
            idx = i;
    if(idx < 0) return vector<int>();
    ll val = 0LL;
    vector<int> ans;
    for(int i = w.size(); i > 0 && idx > 0; i--) {
        ll tmp = val+w[i-1];
        if(tmp >= A[i-1][idx-1].fi && tmp <= A[i-1][idx-1].se) {
            val = tmp;
            idx--;
            ans.push_back(i-1);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
