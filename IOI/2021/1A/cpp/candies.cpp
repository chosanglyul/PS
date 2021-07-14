#include "candies.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) {
    vector<int> ans(c.size(), 0);
    for(int i = 0; i < v.size(); i++) {
        for(int j = l[i]; j <= r[i]; j++) {
            if(v[i] < 0) ans[j] = max(0, ans[j]+v[i]);
            else ans[j] = min(c[j], ans[j]+v[i]);
        }
    }
    return ans;
}
