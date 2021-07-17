#include <bits/stdc++.h>
using namespace std;

bool solve(string& a, string& b) {
	for(int i = 0, j = 0; i < a.size() && j < b.size(); i++)
		if(a[i] == b[j])
			if(++j == b.size())
				return true;
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t; cin >> t;
	while(t--) {
		string x, y, w; cin >> x >> y >> w;
		bool can = false;
		for(char c = 'a'; c <= 'z'; c++) {
			string f = c+w, b = w+c;
			if(solve(x, f) && solve(y, f)) {
				can = true; break;
			}
			if(solve(x, b) && solve(y, b)) {
				can = true; break;
			}
		}
		if(can) cout << "1\n";
		else cout << "0\n";
	}
	return 0;
}
