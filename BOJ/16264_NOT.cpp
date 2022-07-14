#include <bits/stdc++.h>
using namespace std;

const int MAX_ROOT = 316;
const int MAX_N = 1e5 + 1;
const int INF = 1e9;

struct Heap {
    int curr_max;
    vector<int> arr;
    vector<int> bucket;
    Heap() {
        curr_max = -INF;
        arr.resize(MAX_N, 0);
        bucket.resize(MAX_ROOT, 0);
    }
    
    void add(int x) {
        arr[x]++;
        bucket[x / MAX_ROOT]++;
    }
    
    void remove(int x) {
        assert(arr[x] > 0);
        arr[x]--;
        bucket[x / MAX_ROOT]--;
    }

    void calc() {
        int i = (arr.size()-1) / MAX_ROOT;
        while (i >= 0 && bucket[i] == 0) i--;
        if (i == -1) {
            curr_max = -INF;
            return;
        }
        for (int j=(i+1)*MAX_ROOT-1; j>=i*MAX_ROOT; --j) {
            if (arr[j] > 0) {
                curr_max = j;
                return;
            }
        }
    }

    int max() {
        return curr_max;
    }
};

deque<int> arrtmp[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cases;
    cin >> cases;
    while (cases--) {
        int n;
        cin >> n;
        vector<int> arr(n+1);
        for (int i=1; i<=n; ++i) cin >> arr[i];
        for (int i=1; i<=n; ++i) arr[i] += arr[i-1];

        int q;
        cin >> q;
        vector<pair<pair<int, int>, int> > queries(q);
        for (int i=0; i<q; ++i) {
            cin >> queries[i].first.first >> queries[i].first.second;
        }
        sort(queries.begin(), queries.end(), [](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
            if (a.first.first / MAX_ROOT == b.first.first / MAX_ROOT) {
                return a.first.second < b.first.second;
            } else {
                return a.first.first / MAX_ROOT < b.first.first / MAX_ROOT;
            }
        });
        
        const int OFFSET = 1e5;
        for (int i=queries[0].first.first; i<=queries[0].first.second; ++i) {
            arrtmp[arr[i] + OFFSET].push_back(i);
        }

        long long ans = 0;

        Heap heap;
        int l = queries[0].first.first;
        int r = queries[0].first.second;
        for (int i=0; i<=2*OFFSET; ++i) {
            if (arrtmp[i].size() >= 1) heap.add(arrtmp[i].back() - arrtmp[i][0]);
        }
        heap.calc();
        ans += heap.max();

        auto add = [&](int x) {
            int idx = arrtmp[arr[x] + OFFSET];
            if (arrtmp[idx].size() >= 1) heap.remove(arrtmp[idx].back() - arrtmp[idx][0]);
            arrtmp[arr[x] + OFFSET].push_back(x);
            heap.add(arrtmp[idx].back() - arrtmp[idx][0]);
        }

        auto remove = [&](int x) {
            int idx = arrtmp[arr[x] + OFFSET];
            if (arrtmp[idx].size() >= 1) heap.remove(arrtmp[idx].back() - arrtmp[idx][0]);
            arrtmp[arr[x] + OFFSET].push_back(x);
            heap.add(arrtmp[idx].back() - arrtmp[idx][0]);
        }

        for (int i=1; i<q; ++i) {
            while (queries[i].first.second >= r+1) {
                r++;
                arrtmp[]
            } 
        }
        // mos


    }
}