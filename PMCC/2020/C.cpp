#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    cout << n*n+1 << "\n";
    vector<int> A(n, 1), B(n*n+1);
    A[n-1] = 2;
    B[0] = 1, B[n*n] = 1;
    for(int i = 1; i < n*n; i++)
        B[i] = A[B[i-1]-1]++;
    for(auto i : B) cout << i << " ";
    cout << "\n";
    return 0;
}