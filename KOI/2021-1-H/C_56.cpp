#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define fi first
#define se second

vector<pi> solve(string& a, string& b) {
    vector<pi> A(b.size()+1); A[0] = {-1, -1};
    A.push_back({a.size()+1, a.size()+1});
	for(int i = 0, j = 0; i < a.size() && j < b.size(); i++) {
		if(a[i] == b[j]) { A[j+1].fi = i; j++; }
    }
    for(int i = a.size(), j = b.size(); i > 0 && j > 0; i--) {
		if(a[i-1] == b[j-1]) { A[j].se = i; j--; }
    }
    return A;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t; cin >> t;
	while(t--) {
        string x, y, w; cin >> x >> y >> w;
        vector<pi> X = solve(x, w), Y = solve(y, w);
        bool can = false;
        for(char c = 'a'; c <= 'z'; c++) {
            for(int i = 1; i < w.size()+2; i++) {
                pair<bool, bool> tmp = {false, false};
                for(int j = X[i-1].fi+1; j < X[i].se-1; j++)
                    if(x[j] == c) tmp.fi = true;
                for(int j = Y[i-1].fi+1; j < Y[i].se-1; j++)
                    if(y[j] == c) tmp.se = true;
                if(tmp.fi && tmp.se) {
                    can = true;
                    break;
                }
            }
            if(can) break;
        }
        cout << (can ? 1 : 0) << "\n";
	}
	return 0;
}
