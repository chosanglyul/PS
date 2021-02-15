#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    int k = 1;
    for(int i = 1; i < s.size(); i++)
        if(s[i] <= s[i-1]) k++;
    cout << k << "\n";
    return 0;
}