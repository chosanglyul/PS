#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll po(ll a, int b) {
    ll ans = 1LL, tmp = a;
    while(b) {
        if(b&1LL) ans *= tmp;
        tmp *= tmp;
        b >>= 1;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        vector<int> A;
        for(auto i : s) A.push_back(i-'0');
        int n = A.size()-1;
        vector<ll> B;
        for(int i = 0; i < (1<<n); i++) {
            int tmp = A[0], ans = 0;
            for(int j = 0; j < n; j++) {
                if(i&(1<<j)) {
                    ans += tmp;
                    tmp = 0;
                }
                tmp = tmp*10+A[j+1];
            }
            ans += tmp;
            B.push_back(ans);
        }
        sort(B.begin(), B.end());
        B.erase(unique(B.begin(), B.end()), B.end());
        if(B[0] == 1) cout << "Hello, BOJ 2023!\n";
        else {
            int cnt = 0;
            for(int i = 1; i < 100; i++) {
                ll su = 0LL;
                for(auto j : A) su += po(j, i);
                auto iter = lower_bound(B.begin(), B.end(), su);
                if(iter == B.end()) break;
                if(*iter == su) cnt++;
            }
            if(cnt < 99) cout << cnt << "\n";
            else cout << "Hello, BOJ 2023!\n";
        }
    }
    return 0;
}
