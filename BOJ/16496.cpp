#include <bits/stdc++.h>
using namespace std;

bool cmp(string& a, string& b) {
    for(int i = 0; i < 100; i++) {
        if(a[i%a.size()] == b[i%b.size()]) continue;
        return a[i%a.size()] > b[i%b.size()];
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    bool zero = true;
    vector<string> A(n);
    for(auto &i : A) {
        cin >> i;
        if(i != "0") zero = false;
    }
    if(zero) {
        cout << "0";
    } else {
        sort(A.begin(), A.end(), cmp);
        for(auto &i : A) cout << i;
    }
}