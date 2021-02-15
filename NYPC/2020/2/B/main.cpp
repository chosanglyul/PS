#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
int P[404];

int fin(int i) {
    if(P[i] == i) return i;
    return P[i] = fin(P[i]);
}

void mer(int i, int j) {
    i = fin(i), j = fin(j);
    if(i == j) return;
    P[i] = j;
}

int input() {
    int x, y, z;
    scanf("%d:%d:%d", &x, &y, &z);
    return z+100*(y+60*x);
}

int main() {
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) i = input();
    sort(A.begin(), A.end());
    int maxcnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            int cnt = 1;
            for(int k = 0; k <= n; k++) P[k] = k;
            mer(i+1, i), mer(j+1, j);
            for(int k = 0; k < n; k++) {
                if(fin(k+1) != k+1) continue;
                int idx = lower_bound(A.begin(), A.end(), A[i]+A[j]-A[k]+1000)-A.begin()-1;
                if(fin(idx+1) == 0) continue;
                idx = fin(idx+1)-1;
                if(idx == k) {
                    if(fin(idx) == 0) continue;
                    idx = fin(idx)-1;
                }
                if(A[idx] < A[i]+A[j]-A[k]) continue;
                cnt++;
                //cout << k << " " << idx << " " << cnt << endl;
                mer(idx+1, idx);
                mer(k+1, k);
            }
            maxcnt = max(cnt, maxcnt);
        }
    }
    cout << maxcnt << endl;
    return 0;
}