#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n; cin >> n;
	int k = 1;
    while(k*2 <= n) k *= 2;
    cout << k << "\n";
	return 0;
}