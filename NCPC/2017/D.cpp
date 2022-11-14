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
int n, k;
int vis[1<<21];
int input[110000];
queue <int> mq;
vector <int> gan[1<<21];
int bintodec(){
    string ms;
    cin >> ms;
    int re = 0;
    for(int i=0;i<k;i++){
        re*=2;
        re+=ms[i]-'0';
    }
    return re;
}
void dectobin(int su){
    for(int i=k-1;i>=0;i--)
        cout << !!(su&(1<<i));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i=0;i<n;i++)
        input[i] = bintodec();
    for(int i=0;i<(1<<k);i++){
        for(int j=0;j<k;j++)
            gan[i].push_back(i^(1<<j));
    }
    
    for(int i=0;i<n;i++){
        mq.push(input[i]);
        vis[input[i]]=1;
    }
    
    while(mq.size()){
        int u = mq.front();
        mq.pop();
        for(int x : gan[u]) if(!vis[x]){
            mq.push(x);
            vis[x] = vis[u] + 1;
        }
    }

    int dap = 0;
    for(int i=0;i<(1<<k);i++)if(vis[i]>vis[dap])
        dap = i;

    dectobin(dap);
    return 0;
}