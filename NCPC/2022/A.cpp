#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> arr(n);
    for (int i=0; i<n; ++i) {
        string s;
        cin >> s;
        int x, y;
        if (s[1] == '-') {
            x = stoi(s.substr(0, 1));
            y = stoi(s.substr(2));
            
        } else {
            x = stoi(s.substr(0, 2));
            y = stoi(s.substr(3));
        }
        if ((x+y) % 4 == 1 || (x+y) % 4 == 2) {
                arr[i] = { y, x };
            } else {
                arr[i] = { x, y };
            }
    }

    for (int i=0; i<n; ++i) {
        if (arr[i].first == 11 && arr[i].second == 11) {
            cout << "error " << i+1;
            return 0;
        }
        if (i > 0) {
            if (max(arr[i-1].first, arr[i-1].second) == 11) {
                if (arr[i].first != arr[i-1].first || arr[i].second != arr[i-1].second) {
                    cout << "error " << i+1;
                    return 0;
                }
            }
            if (arr[i].first < arr[i-1].first || arr[i].second < arr[i-1].second) {
                cout << "error " << i+1;
                return 0;
            }
        }
    }
    cout << "ok";

    return 0;
}