#include <bits/stdc++.h>
using namespace std;

double dp[60][8100], p[100];
double T;
int n, r, m;
int t[100], l[100],  d[100];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> r >> m;
    for(int i=0;i<m;i++)
        cin >> t[i] >> p[i] >> d[i];
    t[m] = n;
    for(int i=0;i<m;i++)
        l[i] = t[i+1]-t[i];

    double L = 0, R = 1e16;
    for(int cas=0;cas<100;cas++){
        T = (L+R)/2;
        for(int i=m-1;i>=0;i--){
            for(int j=r-n-1;j>=0;j--)
                dp[i][j] = p[i] *(l[i]+dp[i+1][j])+
                            (1-p[i]) * min(dp[i+1][j+d[i]]+l[i]+d[i], T);
        }
        if(dp[0][0]>T)
            L = T;
        else
            R = T;
    }
    cout << fixed << setprecision(15) << T << "\n";

    return 0;
}