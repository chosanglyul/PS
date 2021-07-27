#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve(vector<int>& A) {
    ll su = A[0], ans = -(ll)1e9;
    for(int i = 1; i+1 < A.size(); i++) {
        ans = max(ans, su-A[i]);
        su += A[i];
    }
    return ans+su;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, ma = 0; cin >> n;
    ll su = 0LL;
	vector<int> A(n);
    for(auto &i : A) cin >> i;
    for(int i = 1; i+1 < A.size(); i++) {
        su += A[i];
        ma = max(ma, A[i]);
    }
    ll tmp = max(solve(A), su+ma);
    reverse(A.begin(), A.end());
    cout << max(tmp, solve(A)) << "\n";
	return 0;
}