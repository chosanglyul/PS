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
const ll MD = 1e9+7;
const ll LLINF = (ll)1e18+5;
int dp[210][61][12100];
int N, F;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 60;
        for(int f=1;f<=200;f++){
            for(int nf=0;nf<=n*f;nf++)
                dp[f][0][nf]=1;
            for(int i=1;i<=n;i++){
                for(int nf=0;nf<=n*f;nf++){
                    dp[f][i][nf] = dp[f][i-1][nf];
                    if(nf-f-1>=0)
                        dp[f][i][nf] -= dp[f][i-1][nf-f-1];
                    if(dp[f][i][nf]<0)
                        dp[f][i][nf] += MD;
                    dp[f][i][nf] %= MD;
                }
                for(int nf=1;nf<=n*f;nf++){
                    dp[f][i][nf] += dp[f][i][nf-1];
                    if(dp[f][i][nf]<0)
                        dp[f][i][nf] += MD;
                    dp[f][i][nf] %= MD;
                }
            }
        }
    while(true){
        cin >> N >> F;
        if(N==0&&F==0)
            return 0;
        ll dap=1;
        for(int nf=N-1;nf<=(N-1)*F;nf+=N-1){
            dap += dp[F][N-1][nf]-dp[F][N-1][nf-1];
            if(dap<0)
                dap += MD;
            dap %= MD;
        }
        dap *= N;
        dap %= MD;
        cout << dap << "\n";
    }
    return 0;
}