#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, x;
    int p[20], q[20];
    cin >> n >> x;
    for(int i=1;i<=n;i++)
        cin >> p[i];

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    int dap=0, sum, maxx, imax=0;
    for(int i=1;i<=n;i++)
        imax = max(imax, p[i]);
    do {
        for(int i=0;i<=n;i++)
            q[i]=0;
        q[0]=1;
        sum = 0;
        maxx = imax;
        for(int i=1;i<=n&&sum<=x;i++){
            q[i] = max(maxx-p[perm[i-1]]+1, q[i-1]);
            sum += q[i];
            maxx = p[perm[i-1]]+q[i];
        }
        if(sum<=x)
            dap++;
    } while (next_permutation(perm.begin(), perm.end()));
    cout << dap << "\n";

    return 0;
}