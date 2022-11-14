#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    out << '[';
    for (int i=0; i<arr.size(); ++i) {
        out << arr[i];
        if (i+1 < arr.size()) out << ' ';
    }
    out << ']';
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}