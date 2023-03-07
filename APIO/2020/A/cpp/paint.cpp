#include "paint.h"
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
ostream& operator<<(ostream& os, const deque<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }

int minimumInstructions(int N, int M, int K, vector<int> C, vector<int> A, vector<vector<int>> B) {
    vector<vector<int>> work(K);
    for(int i = 0; i < M; i++)
        for(auto j : B[i])
            work[j].push_back(i);
    vector<vector<int>> can(M);
    for(int i = 0, idx = 0; i < N; i++) {
        for(auto j : work[C[i]]) {
            int tmp = j+idx;
            if(tmp >= M) tmp -= M;
            can[tmp].push_back(i);
        }
        if(--idx < 0) idx += M;
    }
    vector<bool> paint(N, false);
    for(int i = 0; i < M; i++)
        for(int j = M-1, k = 0; j < can[i].size(); j++, k++) 
            if(can[i][j]-can[i][k] == M-1)
                paint[can[i][j]] = true;
    vector<int> dp(N, INF);
    if(paint[M-1]) fill(dp.begin(), dp.begin()+M, 1);
    for(int i = M; i < N; i++) {
        if(!paint[i]) continue;
        dp[i] = min(dp[i], dp[i-M]+1);
        for(int j = i-1; j >= 0 && !paint[j]; j--) dp[j] = dp[i];
    }
    if(dp.back() == INF) return -1;
    else return dp.back();
}
