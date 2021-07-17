#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
#define fi first
#define se second

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k; cin >> n >> k;
	vector<ll> Q(4);
	for(auto &i : Q) cin >> i;
	vector<priority_queue<ll>> A(4);
	for(int i = 0; i < n; i++) {
		char t;
		ll u;
		cin >> t >> u;
		A[t-'A'].push(u);
	}
	for(int i = 0; i < k; i++) {
		vector<int> T;
		for(int i = 0; i < 4; i++) T.push_back(i);
		sort(T.begin(), T.end(), [&](int a, int b) {
			if(A[a].empty()) return false;
			if(A[b].empty()) return true;
			return Q[b]*A[a].top() > Q[a]*A[b].top();
		});
		int tmp = A[T[0]].top();
		A[T[0]].pop();
		Q[T[0]] += tmp;
		cout << (char)(T[0]+'A') << " " << tmp << "\n";
	}
	return 0;
}