#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,sse4a,avx,avx2,popcnt,tune=native")
typedef long long ll;
using namespace std;

struct Node {
    int64_t sum, pref;
    Node() : sum(0), pref(0) {}
    Node(int64_t _val) : sum(_val), pref(_val) {}
    Node(int64_t _sum, int64_t _pref) : sum(_sum), pref(_pref) {}
    Node operator+(const Node &b) const {
        int64_t _sum = sum + b.sum;
        int64_t _pref = max(pref, sum + b.pref);
        return Node(_sum, max(_pref, (int64_t)0));
    }
};

struct SegmentTree {
  private:
    int n;
    vector<int64_t> nums;
    vector<Node> tree;
    void build(int i, int L, int R) {
        if (L == R) {
            tree[i] = Node(nums[L]);
            return;
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        build(x, L, m);
        build(y, m + 1, R);
        tree[i] = tree[x] + tree[y];
    }
    void update(int i, int L, int R, int p, int64_t v) {
        if (L == R) {
            tree[i] = Node(v);
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
    Node query(int i, int L, int R, int l, int r) {
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
            Node q1 = query(x, L, m, l, m);
            Node q2 = query(y, m + 1, R, m + 1, r);
            return q1 + q2;
        }
    }

  public:
    SegmentTree(vector<int64_t> &v) : n(v.size()), nums(v) {
        tree.assign(4 * n, Node());
        build(0, 0, n - 1);
    }
    Node query(int l, int r) { return query(0, 0, n - 1, l, r); }
    void update(int p, int v) { update(0, 0, n - 1, p, v); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int64_t> nums(n);
    for (int i = 0; i < n; ++i) cin >> nums[i];
    SegmentTree tree(nums);
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int p, v;
            cin >> p >> v;
            tree.update(p - 1, v);
        } else {
            int l, r;
            cin >> l >> r;
            Node res = tree.query(l - 1, r - 1);
            cout << max(res.pref, (int64_t)0) << '\n';
        }
    }
}
