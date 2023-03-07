#include "doll.h"
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
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }

void make(int &s, int cnt, int root, int idx, int lvl, vector<int> &X, vector<int> &Y) {
    if(lvl == 2) {
        if(cnt == 1) X[idx] = root;
        else X[idx] = INF;
        Y[idx] = INF;
    } else {
        if(cnt > lvl/2) {
            X[idx] = -(++s);
            X.push_back(0); Y.push_back(0);
            make(s, cnt-lvl/2, root, -X[idx]-1, lvl/2, X, Y);
            Y[idx] = -(++s);
            X.push_back(0); Y.push_back(0);
            make(s, lvl/2, root, -Y[idx]-1, lvl/2, X, Y);
        } else {
            X[idx] = root;
            Y[idx] = -(++s);
            X.push_back(0); Y.push_back(0);
            make(s, cnt, root, -Y[idx]-1, lvl/2, X, Y);
        }
    }
}

void solve(int &c, vector<int> &X, vector<int> &Y, vector<int> &nxt) {
    if(nxt.size() == 0) {
        c = 0;
    } else if(nxt.size() == 1) {
        c = nxt[0];
    } else {
        int s = 0;
        c = -(++s);
        X.push_back(0); Y.push_back(0);
        int lvl = 1;
        while(lvl < nxt.size()) lvl <<= 1;
        make(s, nxt.size(), c, -c-1, lvl, X, Y);
        int here = c, cnt = 0;
        vector<bool> chk(s+c+1, true);
        while(cnt < nxt.size()) {
            //cout << here << " " << c << "\n";
            int& there = (chk[-here+c] ? X[-here-1] : Y[-here-1]);
            chk[-here+c] = !chk[-here+c];
            if(there == INF) {
                there = nxt[cnt++];
                here = c;
            } else here = there;
        }
    }
}

void create_circuit(int M, vector<int> A) {
    vector<int> C(M+1, -1), X, Y;
    A.push_back(0);
    solve(C[0], X, Y, A);
    answer(C, X, Y);
}
