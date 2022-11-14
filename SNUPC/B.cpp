#include <bits/stdc++.h>
using namespace std;

int calc(vector<int>& B, int n) {
    int ans = 0;
    for(int i = 0, j = 1; i < B.size(); i++, j = (j*10)%n) {
        ans = (ans+j*B[i])%n;
    }
    return ans;
}

void dfs(int x, vector<int>& A, vector<bool>& chk, vector<int>& V) {
    if(chk[x]) return;
    chk[x] = true;
    V.push_back(x);
    dfs(A[x], A, chk, V);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; string s; cin >> n >> s;
    vector<int> A(n), B, C(n+1, -1);
    for(auto &i : A) { cin >> i; i--; }
    for(auto c : s) B.push_back(c-'0');
    reverse(B.begin(), B.end());
    vector<vector<int>> V;
    vector<bool> chk(n, false);
    for(int i = 0; i < n; i++) {
        if(!chk[i]) {
            vector<int> T;
            dfs(i, A, chk, T);
            V.push_back(T);
        }
    }
    vector<int> D(n);
    for(auto &i : V) {
        int m = i.size();
        int& tmp = C[m];
        if(tmp == -1) tmp = calc(B, m);
        for(int j = 0; j < m; j++) {
            D[i[j]] = i[(j+tmp)%m];
        }
    }
    for(auto i : D) cout << i+1 << " ";
    cout << "\n";
    return 0;
}