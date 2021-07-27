#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n; cin >> n;
	vector<int> A;
	for(int i = 0; i < n; i++) {
		int x; cin >> x;
		while(A.size() && A.back() <= x) A.pop_back();
		A.push_back(x);
	}
	cout << A.size() << "\n";
	return 0;
}