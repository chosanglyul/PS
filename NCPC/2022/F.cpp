#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> Z(string s) {
    vector<int> ret(s.size(), 0); ret[0] = s.size();
    for(int i = 1, l = 0, r = 1; i < s.size(); i++) {
        ret[i] = max(0, min(ret[i-l], r-i));
        while(ret[i]+i < s.size() && s[i+ret[i]] == s[ret[i]]) ret[i]++;
        if(i+ret[i] > r) r = i+ret[i], l = i;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<string>> A(n, vector<string>(n));
    for(auto &i : A) for(auto &j : i) cin >> j;
    if(n == 2) {
        int m = A[0][1].size();
        bool can = (A[1][0].size() == m);
        int cnt = 0, k;
        vector<int> ZA = Z(A[0][1]+A[1][0]), ZB = Z(A[1][0]+A[0][1]);
        for(int i = 1; i < m && can; i++)
            if(ZA[2*m-i] == i && ZB[m+i] == m-i)
                cnt++, k = i;
        if(cnt == 0) cout << "NONE\n";
        else if(cnt >= 2) cout << "MANY\n";
        else {
            cout << "UNIQUE\n";
            cout << string(A[0][1].begin(), A[0][1].begin()+k) << "\n";
            cout << string(A[0][1].begin()+k, A[0][1].end()) << "\n";
        }
    } else {
        int m = (int)A[0][1].size()+(int)A[0][2].size()-(int)A[1][2].size();
        if((m&1) || m <= 0) {
            cout << "NONE\n";
        } else {
            m >>= 1;
            if(m >= A[0][1].size()) {
                cout << "NONE\n";
                return 0;
            }
            vector<string> S(n);
            S[0] = string(A[0][1].begin(), A[0][1].begin()+m);
            for(int i = 1; i < n; i++) {
                if(m >= A[0][i].size()) {
                    cout << "NONE\n";
                    return 0;
                }
                S[i] = string(A[0][i].begin()+m, A[0][i].end());
            }
            bool can = true;
            for(auto &i : S) can = (can && i.size());
            for(int i = 0; i < n && can; i++) {
                for(int j = 0; j < n && can; j++) {
                    if(i == j) continue;
                    can = (can && A[i][j] == S[i]+S[j]);
                }
            }
            if(can) {
                cout << "UNIQUE\n";
                for(auto &i : S) cout << i << "\n";
            } else cout << "NONE\n";
        }
    }
    return 0;
}