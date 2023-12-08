#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int DPMX=100000;
ll dp[110000];
int n,q,m;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i=1;i<=n;i++)
        cin >> dp[i];
    for(int i=n+1;i<=DPMX;i++){
        dp[i] = 1e18;
        for(int j=1;j<=n;j++)
            dp[i] = min(dp[i], dp[i-j]+dp[j]);
    }
    m=1;
    for(int i=2;i<=DPMX;i++)if(dp[m]*i > dp[i]*m)
        m = i;
    
    while(q--){
        int k;
        cin >> k;
        if(k<=DPMX)
            cout << dp[k] << "\n";
        else{
            ll mq = (k-DPMX)/m;
            ll dap = mq * dp[m];
            while(k-m*mq>=DPMX){
                dap += dp[m];
                mq++;
            }
            cout << dap + dp[k-m*mq] << "\n";
        }
    }

    return 0;
}