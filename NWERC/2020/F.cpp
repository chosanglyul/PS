#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Fraction {
    ll num, deno;
};

bool operator<(const Fraction& a, const Fraction& b) {
    return a.num * b.deno < a.deno * b.num;
}

struct Event {
    Fraction t;
    int a, b;
};

bool operator<(const Event& a, const Event& b) {
    return a.t < b.t;
}

pair<bool, Fraction> collision(pair<ll, ll> a, pair<ll, ll> b) {
    assert(a.first < b.first);
    if (a.second <= b.second) return { false, {0,0} };
    return { true, { b.first - a.first, b.second - a.second } };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<pair<ll, ll>> arr(n);
    for (int i=0; i<n; ++i) {
        int x, v;
        cin >> x >> v;
        arr[i] = { x, v };
    }

    priority_queue<Event> pq;
    for (int i=0; i+1<n; ++i) {
        auto ret = collision(arr[i], arr[i+1]);
        if (ret.first) {
            pq.push({ ret.second, i, i+1 });
        }
    }

    set<int> alive;
    for (int i=0; i<n; ++i) alive.insert(i);
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();
        // cout << curr.a << ' ' << curr.b << endl;
        if (alive.find(curr.a) == alive.end() || alive.find(curr.b) == alive.end()) continue;
        auto ita = alive.find(curr.a);
        auto itb = alive.find(curr.b);
        if (ita == alive.begin() || next(itb) == alive.end()) {
            alive.erase(ita);
            alive.erase(itb);
            continue;
        }
        int newa = *prev(ita);
        int newb = *next(itb);
        alive.erase(ita);
        alive.erase(itb);
        auto ret = collision(arr[newa], arr[newb]);
        if (ret.first) {
            pq.push({ ret.second, newa, newb });
        }
    }

    cout << alive.size() << '\n';
    for (int x: alive) cout << x+1 << ' ';

    return 0;
}