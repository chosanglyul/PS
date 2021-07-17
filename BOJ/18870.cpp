#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    map<int, int> M;
    for(auto i : A) M[i]++;
    int tmp = 0;
    for(auto &i : M) i.se = tmp++;
    for(auto i : A) cout << M[i] << " ";
    return 0;
}