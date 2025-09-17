<<<<<<< HEAD
=======
#include <algorithm>
#include <cmath>
>>>>>>> 72e167d02ef3b52ed29816ce2b7f266c566f0e21
#include <iostream>
#include <queue>
#include <set>
#include <vector>
<<<<<<< HEAD
#include <algorithm>
typedef long long ll;
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> b(n);
    for (int &i : b) cin >> i;
    
}
=======
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,sse4a,avx,avx2,popcnt,tune=native")
typedef long long ll;
using namespace std;

struct Query {
    int type, a, b;
};

struct SegmentTree {
  private:
    int n;
    vector<int> nums;
    vector<int> tree;
    void build(int i, int L, int R) {
        if (L == R) {
            tree[i] = nums[L];
            return;
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        build(x, L, m);
        build(y, m + 1, R);
        tree[i] = tree[x] + tree[y];
    }
    void update(int i, int L, int R, int p, int v) {
        if (L == R) {
            tree[i] += v;
            return;
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (p <= m) {
            update(x, L, m, p, v);
        } else {
            update(y, m + 1, R, p, v);
        }
        tree[i] = tree[x] + tree[y];
    }
    int query(int i, int L, int R, int l, int r) {
        if (L == l && r == R) {
            return tree[i];
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (r <= m) {
            return query(x, L, m, l, r);
        } else if (l > m) {
            return query(y, m + 1, R, l, r);
        } else {
            int q1 = query(x, L, m, l, m);
            int q2 = query(y, m + 1, R, m + 1, r);
            return q1 + q2;
        }
    }

  public:
    SegmentTree(vector<int> &v) : n(v.size()), nums(v) {
        tree.assign(4 * n, 0);
        build(0, 0, n - 1);
    }
    void update(int p, int v) { update(0, 0, n - 1, p, v); }
    int query(int l, int r) { return query(0, 0, n - 1, l, r); }
};
>>>>>>> 72e167d02ef3b52ed29816ce2b7f266c566f0e21

int main(){
    cin.tie(0)->sync_with_stdio(0);
<<<<<<< HEAD
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
=======
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    vector<int> c(n);
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        c[i] = nums[i];
        mx = max(mx, nums[i]);
    }
    vector<Query> qs(q);
    for (int i = 0; i < q; ++i) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        if (t == '!') {
            c.push_back(b);
            qs[i] = {0, a, b};
        } else {
            c.push_back(a);
            c.push_back(b);
            qs[i] = {1, a, b};
        }
    }
    sort(c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    // vector<int> freq(c.size() + 1, 0);
    vector<int> freq(mx + 1, 0);
    for (int &i : nums) {
        // i = lower_bound(c.begin(), c.end(), i) - c.begin();
        ++freq[i];
    }

    SegmentTree tree(freq);
    for (int i = 0; i < freq.size(); ++i) {
        cout << tree.query(i, i) << ' ';
    }
    cout << '\n';
    for (Query &x : qs) {
        if (x.type == 0) {
            // x.b = lower_bound(c.begin(), c.end(), x.b) - c.begin();
            int p = x.a - 1;
            int v = x.b;
            --p;
            tree.update(nums[p], -1);
            nums[p] = v;
            tree.update(nums[p], 1);
            for (int i = 0; i < freq.size(); ++i) {
                cout << tree.query(i, i) << ' ';
            }
            cout << '\n';
        } else {
            // x.b = lower_bound(c.begin(), c.end(), x.b) - c.begin();
            // x.a = lower_bound(c.begin(), c.end(), x.a) - c.begin();
            int a = x.a;
            int b = x.b;
            cout << tree.query(a, b) << '\n';
        }
>>>>>>> 72e167d02ef3b52ed29816ce2b7f266c566f0e21
    }
}