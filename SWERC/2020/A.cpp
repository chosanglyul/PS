#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<pair<string, int>> S;
    string s;
    getline(cin, s);
    for(int i = 0; i < 3*n; i++) {
        getline(cin, s);
        S.push_back({s, i});
    }
    vector<pair<string, int>> SS(S);
    sort(S.begin(), S.end());
    vector<pair<int, int>> P;
    for(int i = 0; i < S.size(); i++) {
        if(i == 0 || S[i].fi != S[i-1].fi) {
            P.push_back({0, S[i].se});
        } else {
            P.back().se = S[i].se;
        }
        P.back().fi++;
    }
    // cout << "S = " << "\n";
    // for(auto &i : S) cout << i.fi << "\n";
    // for(auto &i : P) cout << i.fi << " " << i.se << "\n";
    sort(P.begin(), P.end(), greater<pair<int, int>>());
    for(int i = 0; i < min((int)P.size(), k); i++) {
        cout << SS[P[i].se].fi << "\n";
    }
    return 0;
}