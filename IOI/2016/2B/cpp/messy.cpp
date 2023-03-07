#include "messy.h"
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


string b2s(vector<bool> &A) {
    string s;
    for(auto i : A) s += (i ? '1' : '0');
    return s;
}

void add(int n, int s, int e) {
    if(s+1 == e) return;
    vector<bool> A(n);
    for(int i = 0; i < n; i++) {
        if(i >= s && i < e) A[i] = false;
        else A[i] = true;
    }
    int mi = s+e>>1;
    for(int i = s; i < mi; i++) {
        A[i] = true;
        add_element(b2s(A));
        A[i] = false;
    }
    add(n, s, mi);
    add(n, mi, e);
}

vector<int> solve(int n, int s, int e, vector<bool> A) {
    if(s+1 == e) {
        vector<int> ret(n, -1);
        for(int i = 0; i < n; i++) if(!A[i]) ret[i] = s;
        return ret;
    }
    vector<bool> B(A), C(A);
    for(int i = 0; i < n; i++) {
        if(A[i]) continue;
        A[i] = true;
        bool x = check_element(b2s(A));
        A[i] = false;
        B[i] = x, C[i] = !x;
    }
    int mi = s+e>>1;
    vector<int> L = solve(n, s, mi, C);
    vector<int> R = solve(n, mi, e, B);
    vector<int> ret(n, -1);
    for(int i = 0; i < n; i++) {
        if(L[i] != -1) ret[i] = L[i];
        if(R[i] != -1) ret[i] = R[i];
    }
    return ret;
}

vector<int> restore_permutation(int n, int w, int r) {
    add(n, 0, n);
    compile_set();
    return solve(n, 0, n, vector<bool>(n, false));
}
