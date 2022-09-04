#include <bits/stdc++.h>
using namespace std;

vector<int> get_cnt(string& s) {
    vector<int> A;
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'b') {
            A.push_back(cnt);
            cnt = 0;
        } else cnt++;
    }
    A.push_back(cnt);
    return A;
}

vector<int> get_psu(vector<int> A, bool rev) {
    if(rev) reverse(A.begin(), A.end());
    vector<int> R(1, 0);
    for(auto i : A) R.push_back(R.back()+i);
    R.erase(R.begin());
    if(rev) reverse(R.begin(), R.end());
    return R;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        int n, m; cin >> n >> m;
        string a, b; cin >> a >> b;
        vector<int> A = get_cnt(a), B = get_cnt(b);
        int sa = A.size(), sb = B.size();
        cout << "Case #" << _t+1 << endl;
        if(sa < sb) {
            cout << "NO" << endl;
        } else {
            vector<bool> mat(sa-sb+1, true);
            if(*max_element(B.begin(), B.end())) {
                int st = 0, ed = B.size();
                while(B[st] == 0) { st++; }
                do { ed--; } while(B[ed] == 0);
                vector<int> P = (B.front() ? get_psu(A, false) : A);
                vector<int> Q = (B.back() ? get_psu(A, true) : A);
                for(int i = 0; i < mat.size(); i++) {
                    if(st == ed) mat[i] = max(P[st+i], Q[ed+i]) >= B[st];
                    else mat[i] = (P[st+i] >= B[st] && Q[ed+i] >= B[ed]);
                    for(int j = st+1; j < ed; j++) mat[i] = (mat[i] && (A[i+j] == B[j]));
                }
            }
            bool can = false;
            for(auto i : mat) can = (can || i);
            if(can) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}