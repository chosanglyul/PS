#include "magic.h"
#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9+5;

int calc(int x, int l, int r) {
	if(x < l || x > r) return 0;
	return abs(x-(l+r)/2);
}

int magic_score(int N, int K, int L[], int R[]) {
	vector<vector<int>> dp(N+1, vector<int>(K+1, 0)), btr(N+1, vector<int>(K+1, 0));
	for(int i = 0; i < K; i++) dp[0][i] = -INF;
	for(int i = 1; i <= N; i++) {
		for(int j = 0; j <= K; j++) {
			if(dp[i-1][j] != -INF) dp[i][j] = dp[i-1][j]+calc(0, L[i-1], R[i-1]);
			else dp[i][j] = -INF;
			if(j+abs(L[i-1]) <= K) {
				int tmp = dp[i-1][j+abs(L[i-1])]+calc(L[i-1], L[i-1], R[i-1]);
				if(tmp > dp[i][j]) {
					dp[i][j] = tmp;
					btr[i][j] = L[i-1];
				}
			}
			if(j+abs(R[i-1]) <= K) {
				int tmp = dp[i-1][j+abs(R[i-1])]+calc(R[i-1], L[i-1], R[i-1]);
				if(tmp > dp[i][j]) {
					dp[i][j] = tmp;
					btr[i][j] = R[i-1];
				}
			}
			if(L[i-1] < -K+j && K-j < R[i-1]) {
				int a = calc(K-j, L[i-1], R[i-1]), b = calc(-K+j, L[i-1], R[i-1]);
				int tmp = dp[i-1][K]+max(a, b);
				if(tmp > dp[i][j]) {
					dp[i][j] = tmp;
					btr[i][j] = (a > b ? K-j : -K+j);
				}
			}
		}
	}
	vector<int> A;
	auto iter = max_element(dp.back().begin(), dp.back().end());
	int idx = iter - dp.back().begin();
	for(int i = N; i > 0; i--) {
		A.push_back(btr[i][idx]);
		idx += abs(btr[i][idx]);
	}
	reverse(A.begin(), A.end());
	for(auto i : A) trick(i);
	return *iter;
}
