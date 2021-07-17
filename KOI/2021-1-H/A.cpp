#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t; cin >> t;
	while(t--) {
		ll n, m, k, d;
		cin >> n >> m >> k >> d;
		ll tmp = k*n*m*(m-1)/2LL+m*m*n*(n-1)/2LL;
		if(tmp > d) cout << -1 << "\n";
		else cout << tmp*(d/tmp) << "\n";
	}
	return 0;
}