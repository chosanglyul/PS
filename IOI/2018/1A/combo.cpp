#include "combo.h"
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

string guess_sequence(int N) {
    string a = "ABXY";
    string s;
    if(press("AB")) {
        if(press("A")) s += 'A';
        else s += 'B';
    } else {
        if(press("X")) s += 'X';
        else s += 'Y';
    }
    if(N == 1) return s;
    a.erase(a.find(s[0]), 1);
    for(int i = 1; i < N-1; i++) {
        int q = press(s+a[0]+s+a[1]+a[0]+s+a[1]+a[1]+s+a[1]+a[2]);
        if(q == s.length()) s += a[2];
        else if(q == s.length()+1) s += a[0];
        else s += a[1];
    }
    if(press(s+a[0]) == N) s += a[0];
    else if(press(s+a[1]) == N) s += a[1];
    else s += a[2];
    return s;
}
