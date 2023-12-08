#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int get(vector<bool> &chk) {
    for(int j = 0; j < chk.size(); j++) {
        if(!chk[j]) {
            chk[j] = true;
            return j+1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> A(n), B(m);
    vector<bool> chk(n+m, false);
    bool x = true, y = true;
    for(auto &i : A) {
        cin >> i;
        if(i) chk[i-1] = true, x = false;
    }
    for(auto &i : B) {
        cin >> i;
        if(i) chk[i-1] = true, y = false;
    }
    if(y) {
        A.push_back(n+m+2);
        B.push_back(n+m+1);
    } else {
        A.push_back(n+m+1);
        B.push_back(n+m+2);
    }
    int i = 0, j = 0;
    while(i < n || j < m) {
        while(i < n && A[i] == 0) i++;
        while(j < m && B[j] == 0) j++;
        if(A[i] < B[j]) {
            int k = i-1;
            while(k >= 0 && A[k] == 0) k--;
            int tmp = A[k++];
            while(k < i) A[k++] = get(chk, tmp);
        } else {
            int k = j-1;
            while(k >= 0 && B[k] == 0) k--;
            k++;
            while(k < j) B[k++] = get(chk, B[j]);
        }
        if(i < n) i++;
        if(j < m) j++;
    }
    int k;
    k = n-1;
    while(k >= 0 && A[k] == 0) k--;
    k++;
    while(k < n) A[k++] = get(chk);
    k = m-1;
    while(k >= 0 && B[k] == 0) k--;
    k++;
    while(k < m) B[k++] = get(chk);
    A.pop_back();
    B.pop_back();
    for(auto i : A) cout << i << " ";
    cout << "\n";
    for(auto i : B) cout << i << " ";
    cout << "\n";
    return 0;
}