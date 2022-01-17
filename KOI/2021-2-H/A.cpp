#include <bits/stdc++.h>
using namespace std;
const int P = 1000000007;

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	int t; cin >> t;
    int a = 50000, b = 50000, k = 1;
	while(k*(k+1)/2 <= a+b) k++;
	vector<vector<int>> A(k, vector<int>(a+b+1, 0));
    vector<vector<int>> B(k, vector<int>(a+b+2, 0));
	A[0][0] = 1;
	for(int i = 1; i < k; i++) {
		for(int j = 0; j < a+b+1; j++) {
			if(j-i >= 0) A[i][j] = (A[i-1][j-i]+A[i-1][j])%P;
            else A[i][j] = A[i-1][j];
		}
	}
    for(int i = 0; i < k; i++)
        for(int j = 1; j < a+b+2; j++)
            B[i][j] = (B[i][j-1]+A[i][j-1])%P;
	while(t--) {
		cin >> a >> b;
		int ans = 0;
        k = 1;
        while(k*(k+1)/2 <= a+b) k++;
		for(int i = 1; i < k; i++) {
			int tmp = i*(i+1)/2;
			int l = max(0, tmp-b), r = min(tmp, a);
            ans = (((ans+B[i][r+1])%P-B[i][l])%P+P)%P;
		}
		cout << ans << "\n";
	}
	return 0;
}


