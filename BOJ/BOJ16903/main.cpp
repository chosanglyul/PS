#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Trie {
    int ter = 0;
    vector<Trie*> next = vector<Trie*>(2, nullptr);

    ~Trie() {
        for(auto &i : next)
            if(i) delete i;
    }

    void insert(vector<int>& arr, int i) {
        if(i == arr.size()) ter++;
        else {
            if(!next[arr[i]])
                next[arr[i]] = new Trie();
            next[arr[i]]->insert(arr, i+1);
        }
    }

    bool erase(vector<int>& arr, int i) {
        if(i == arr.size()) {
            ter--;
            if(!ter) {
                delete this;
                return true;
            }
        } else if(next[arr[i]]->erase(arr, i+1)) {
            next[arr[i]] = nullptr;
            if((next[0] == nullptr) && (next[1] == nullptr)) {
                delete this;
                return true;
            }
        }
        return false;
    }
};

vector<int> itov(int n) {
    vector<int> res(30, 0);
    for(int i = 0; i < 30; i++, n>>=1)
        res[i] = n&1;
    reverse(res.begin(), res.end());
    return res;
}

int vtoi(vector<int> X) {
    int res = 0;
    reverse(X.begin(), X.end());
    for(int i = 0, t = 1; i < 30; i++, t<<=1)
        res += t*X[i];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Trie* root = new Trie();
    vector<int> Z = itov(0);
    root->insert(Z, 0);
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        vector<int> X = itov(y);
        if(x == 1) root->insert(X, 0);
        else if(x == 2) root->erase(X, 0);
        else {
            Trie* tmp = root;
            vector<int> res(30);
            for(auto &j : X) j = 1-j;
            for(int j = 0; j < 30; j++) {
                if(tmp->next[X[j]]) {
                    res[j] = 1;
                    tmp = tmp->next[X[j]];
                } else {
                    res[j] = 0;
                    tmp = tmp->next[1-X[j]];
                }
            }
            cout << vtoi(res) << "\n";
        }
    }
    return 0;
}