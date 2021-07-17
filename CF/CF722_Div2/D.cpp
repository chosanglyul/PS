#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 998244353;

int solve(int n) {
    int ret = 1;
    for(int i = 2; i*i <= n; i++) {
        int cnt = 0;
        while(n%i == 0) {
            n /= i;
            cnt++;
        }
        ret = (int)((ll)ret*(cnt+1))%P;
    }
    if(n > 1) return (ret*2)%P;
    else return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int a = 1, b = 0;
    for(int i = 1; i <= n; i++) {
        a = (b+solve(i))%P;
        b = (b+a)%P;
    }
    cout << a << "\n";
    return 0;
}