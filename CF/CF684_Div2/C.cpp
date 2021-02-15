#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<bool>> A(n);
        vector<vector<pi>> B;
        for(auto &i : A) {
            string s; cin >> s;
            for(int j = 0; j < m; j++)
                i.push_back(s[j] == '1');
        }
        for(int i = 0; i < n-2; i++) {
            for(int j = 0; j < m-1; j++) {
                vector<pi> tmp(3);
                if(A[i][j] && A[i][j+1]) {
                    tmp[0] = {i+1, j+1}, tmp[1] = {i+1, j+2};
                    if(A[i+1][j]) tmp[2] = {i+2, j+1};
                    else tmp[2] = {i+2, j+2};
                } else if(A[i][j]) tmp[0] = {i+1, j+1}, tmp[1] = {i+2, j+1}, tmp[2] = {i+2, j+2};
                else if(A[i][j+1]) tmp[0] = {i+1, j+2}, tmp[1] = {i+2, j+1}, tmp[2] = {i+2, j+2};
                else continue;
                for(auto &j : tmp) A[j.fi-1][j.se-1] = !A[j.fi-1][j.se-1];
                B.push_back(tmp);
            }
        }
        for(int j = 0; j < m-2; j++) {
            vector<pi> tmp(3);
            if(A[n-1][j] && A[n-2][j]) {
                tmp[0] = {n, j+1}, tmp[1] = {n-1, j+1};
                if(A[n-1][j+1]) tmp[2] = {n, j+2};
                else tmp[2] = {n-1, j+2};
            } else if(A[n-1][j]) tmp[0] = {n, j+1}, tmp[1] = {n-1, j+2}, tmp[2] = {n, j+2};
            else if(A[n-2][j]) tmp[0] = {n-1, j+1}, tmp[1] = {n-1, j+2}, tmp[2] = {n, j+2};
            else continue;
            for(auto &j : tmp) A[j.fi-1][j.se-1] = !A[j.fi-1][j.se-1];
            B.push_back(tmp);
        }
        while(true) {
            vector<pi> tmp;
            for(int i = n-2; i < n; i++)
                for(int j = m-2; j < m; j++)
                    if(A[i][j]) tmp.push_back({i+1, j+1});
            //cout << "1    " << tmp.size() << endl;
            if(tmp.size()) {
                if(tmp.size() == 4) tmp.pop_back();
                else if(tmp.size() < 3) {
                    if(tmp.size() == 2) tmp.pop_back();
                    for(int i = n-2; i < n; i++)
                        for(int j = m-2; j < m; j++)
                            if(!A[i][j]) tmp.push_back({i+1, j+1});
                    //cout << "2    " << tmp.size() << endl;
                    if(tmp.size() == 4) tmp.pop_back();
                }
                for(auto &j : tmp) A[j.fi-1][j.se-1] = !A[j.fi-1][j.se-1];
            } else break;
            //cout << "3    " << tmp.size() << endl;
            B.push_back(tmp);
        }
        cout << B.size() << "\n";
        for(auto &i : B) {
            for(auto &j : i) cout << j.fi << " " << j.se << " ";
            cout << "\n";
        }
    }
    return 0;
}