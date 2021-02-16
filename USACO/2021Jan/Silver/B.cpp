#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

void solve(vector<int>& A, string& s) {
    vector<char> S;
    for(int i = 0; i < s.size(); i++) {
        A[i+1] = A[i];
        while(S.size() && S.back() > s[i]) S.pop_back();
        if(!S.size() || S.back() < s[i]) {
            S.push_back(s[i]);
            A[i+1]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<int> A(n+1, 0), B(n+1, 0);
    solve(A, s);
    reverse(s.begin(), s.end());
    solve(B, s);
    while(q--) {
        int a, b; cin >> a >> b;
        cout << A[a-1]+B[n-b] << "\n";
    }
    return 0;
}