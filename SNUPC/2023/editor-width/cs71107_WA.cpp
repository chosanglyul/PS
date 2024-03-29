#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5+10;

char S[MAXN];
int dp[MAXN];
int ddp[MAXN];
int id[MAXN];
vector<int> fac[MAXN];

int chk[MAXN];

int main()
{
    int n, k;

    ios_base::sync_with_stdio(false);

    cin>>n>>k;

    cin>>(S+1);

    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        if(S[i]^S[i-1]) dp[i] = 1;
        else dp[i] = dp[i-1]+1;
    }

    ddp[n+1] = 0;
    for(int i = n; i >= 1; i--) {
        if(S[i]^S[i+1]) ddp[i] = 1;
        else ddp[i] = ddp[i+1]+1;
    }

    id[0] = 0;

    for(int i = 1; i <= n; i++) {
        if(dp[i] >= k) id[i] = i;
        else id[i] = id[i-1];
    }

    int m = 0;

    for(int i = k; i <= n; i++) {
        for(int j = i; j <= n; j+= i) {
            fac[j].push_back(i);
            m = k+(j-id[j]);
            if(m <= i) chk[i] = 1;
        }
    }

    int cur = 0;

    for(int i = k; i <= n; i++) {
        int fsz = (int)fac[i].size();
        int vv = max(dp[i], ddp[i+1]);

        for(int j = 0; j < fsz; j++) {
            cur = min(vv, fac[i][j]);            
            if(cur >= k) chk[fac[i][j]] = 1;
        }
    }

    int res = k-1;

    for(int i = k; i <= n; i++) {
        if(!chk[i]) res = i;
    }

    cout<<res<<"\n";

    return 0;
}
