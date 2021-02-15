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
    for(int i = 0; i < 14; i++) {
        for(int j = 0; j < 30; j++)
            cout << ((j==15) ? "16 " : "0 ");
        cout << "\n";
    }
    for(int i = 0; i < 15; i++)
        cout << "1 ";
    cout << "0 ";
    for(int i = 0; i < 14; i++)
        cout << "240 ";
    cout << "\n";
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 30; j++)
            cout << ((j==15) ? "3600 " : "0 ");
        cout << "\n";
    }
    return 0;
}