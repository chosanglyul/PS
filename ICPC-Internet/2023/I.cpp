#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
int n;
pii jap[11000], vw[11000];
int dp[11000];
int sor[11000];
const int INF = (int)1e9+5;

bool comp(int a, int b){
    return vw[a].se < vw[b].se;
}
int dis(pii a, pii b){
    return abs(a.fi-b.fi)+abs(a.se-b.se);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i=0;i<n;i++)
        cin >> jap[i].fi >> jap[i].se;
    jap[n] = {0, 0};
    for(int i=0;i<n;i++)
        cin >> vw[i].fi >> vw[i].se;
    vw[n] = {0, 0};
    n++;

    for(int i=0;i<n;i++)
        sor[i] = i;
    sort(sor, sor+n, comp);

    for(int i=0;i<n;i++){
        int now = sor[i];
        if(i) dp[now] = -INF;
        else dp[now] = 0;
        for(int j=0;j<i;j++){
            int zun = sor[j];
            int zdp = vw[zun].se+dis(jap[now], jap[zun]);
            if(zdp<vw[now].se)
                dp[now] = max(dp[now], dp[zun]+vw[now].se-max(vw[now].fi, zdp));
        }
    }
    int dap = 0;
    for(int i=0;i<n;i++)
        dap = max(dap, dp[i]);
    cout << dap << "\n";

    return 0;
}