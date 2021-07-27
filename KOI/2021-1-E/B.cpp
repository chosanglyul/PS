#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n; cin >> n;
	vector<ll> A(n), B(1, 0LL);
    for(auto &i : A) cin >> i;
    for(int i = 0; i < n; i++) B.push_back(B.back()+A[i]);
    ll su = B.back();
    vector<ll> L(n+1, 0LL), R(n+1, 0LL);
    for(int i = 1; i <= n; i++) {
        L[i] = L[i-1];
        if(B[i]*4LL == su*1LL) L[i]++;
    }
    for(int i = n-1; i >= 0; i--) {
        R[i] = R[i+1];
        if(B[i]*4LL == su*3LL) R[i]++;
    }
    ll cnt = 0LL;
    for(int i = 1; i < n; i++)
        if(B[i]*2LL == su)
            cnt += L[i-1]*R[i+1];
    cout << cnt << "\n";
	return 0;
}