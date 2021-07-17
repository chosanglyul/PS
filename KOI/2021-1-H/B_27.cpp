#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define fi first
#define se second

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k; cin >> n >> k;
	priority_queue<pi, vector<pi>, greater<pi>> Q;
	for(int i = 0; i < 4; i++) {
		int x; cin >> x;
		Q.push({x, i});
	}
	vector<priority_queue<int>> A(4);
	for(int i = 0; i < n; i++) {
		char t;
		int u;
		cin >> t >> u;
		A[t-'A'].push(u);
	}
	for(int i = 0; i < k; ) {
		pi tmp = Q.top();
		Q.pop();
		//cout << tmp.fi << " " << tmp.se << " " << A[tmp.se].size() << "\n";
		if(A[tmp.se].size()) {
			int u = A[tmp.se].top();
			A[tmp.se].pop();
			Q.push({tmp.fi+u, tmp.se});
			cout << (char)(tmp.se+'A') << " " << u << "\n";
			i++;
		}
	}
	return 0;
}
