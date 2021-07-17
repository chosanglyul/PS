#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fib(int n) {
    if(n <= 1) return n;
    return fib(n-1)+fib(n-2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    cout << fib(n) << "\n";
    return 0;
}