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

vector<int> cnt(string& a, char c) {
    vector<int> A(a.size()+1, 0);
    for(int i = 1; i <= a.size(); i++) {
        A[i] = A[i-1];
        if(a[i-1] == c) A[i]++;
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
            vector<int> A = cnt(x, c), B = cnt(y, c);
            for(int i = 1; i < w.size()+2; i++) {
                if(A[X[i].se-1]-A[X[i-1].fi+1] > 0 && B[Y[i].se-1]-B[Y[i-1].fi+1] > 0) {
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
