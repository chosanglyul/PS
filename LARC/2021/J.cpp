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

    ll w, h, n;
    cin >> w >> h >> n;

    vector<pair<ll, int>> points;
    for (int i=0; i<n; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (!(x1 == 0 || x1 == w || y1 == 0 || y1 == h) || !(x2 == 0 || x2 == w || y2 == 0 || y2 == h)) continue;
        if (y1 == 0) {
            points.push_back({ x1, i });
        } else if (x1 == w) {
            points.push_back({ w+y1, i });
        } else if (y1 == h) {
            points.push_back({ w+h+w-x1, i });
        } else if (x1 == 0) {
            points.push_back({ w+h+w+h-y1, i });
        }
        if (y2 == 0) {
            points.push_back({ x2, i });
        } else if (x2 == w) {
            points.push_back({ w+y2, i });
        } else if (y2 == h) {
            points.push_back({ w+h+w-x2, i });
        } else if (x2 == 0) {
            points.push_back({ w+h+w+h-y2, i });
        }
    }
    sort(points.begin(), points.end());

    vector<int> st;
    for (int i=0; i<points.size(); ++i) {
        int idx = points[i].second;
        if (st.empty()) st.push_back(idx);
        else if (st.back() == idx) st.pop_back();
        else st.push_back(idx);
    }
    cout << (st.empty() ? 'Y' : 'N');

    return 0;
}