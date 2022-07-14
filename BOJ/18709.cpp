#include <bits/stdc++.h>
using namespace std;
double input[400][400];
double p[400];
int n,k,t;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(5) << fixed;
    cin >> t;
    while(t--){
        cin >> n >> k;
        double sum=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cin >> input[i][j];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                p[1] = (double)(i+1)*(j+1)*(n-i)*(n-j)*2*2/(n+1)/n/(n+1)/n;
                for(int r=2;r<=k;r++)
                    p[r]=(1-2*p[1])*p[r-1]+p[1];
                sum+=input[i][j]*(1-2*p[k])+p[k];
            }
        }
        cout << sum << endl;
    }
    return 0;
}