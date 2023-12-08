#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define ff first
#define ss second

int f(vector<int> V, int x)
{
    int n = V.size();
    int cnt[n + 1] = {};
    for(auto i : V)
    {
        i &= x;
        if(i <= n) ++cnt[i];
    }
    for(int i = 0; i <= n; ++i) if(!cnt[i]) return i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while(T--)
    {
        int n; cin >> n;
        vector<int> V(n);
        for(auto &i : V) cin >> i;
        pii ans = {-1, -1};
        for(int i = 0; i <= 30; ++i)
            ans = max(ans, pii{f(V, (1 << i) - 1), (1 << i) - 1});
        cout << ans.ss << '\n';
    }

    return 0;
}