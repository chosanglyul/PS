#include "prison.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

vector<vector<int>> devise_strategy(int N) {
    vector<vector<int>> B = {{0}, {1, 0}, {1, 4}, {2, 0}, {2, 4}, {4}};
    while(B.size() < 5000) {
        vector<vector<int>> T;
        T.push_back({0});
        for(int i = 1; i <= 3; i++) {
            for(auto &v : B) {
                vector<int> V(v.size()+1); V[0] = i;
                copy(v.begin(), v.end(), V.begin()+1);
                T.push_back(V);
            }
        }
        T.push_back({4});
        B = T;
    }
    //for(int i = 0; i < N; i++) cout << B[i];

    vector<vector<int>> A(21, vector<int>(N+1, 0));
    for(int i = 0; i < A.size(); i++) {
        int tmp = (i+2)/3, num = (i+2)%3+1;
        A[i][0] = tmp%2;
        for(int j = 1; j <= N; j++) {
            vector<int> &T = B[j-1];
            if(T.size()+1 <= tmp) {
                A[i][j] = 0;
            } else if(i && num < T[tmp-1]) {
                A[i][j] = -(2-A[i][0]);
            } else if(i && num > T[tmp-1]) {
                A[i][j] = -(A[i][0]+1);
            } else if(T.size() <= tmp) {
                A[i][j] = 0;
            } else if(T[tmp] == 0) {
                A[i][j] = -(A[i][0]+1);
            } else if(T[tmp] == 4) {
                A[i][j] = -(2-A[i][0]);
            } else {
                A[i][j] = 3*tmp+T[tmp];
            }
        }
    }
    //cout << " " << A;
    return A;
}
