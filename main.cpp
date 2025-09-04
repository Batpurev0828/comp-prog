#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct SegmentTree {
    struct Node {
        int mx, sum;
        Node() : sum(0) {}
        Node(int _val) : sum(_val), mx(_val) {}
        Node(int _sum, int _mx) : sum(_sum), mx(_mx) {}
        Node operator+(const Node &b) { return Node(sum + b.sum, max(mx, b.mx)); }
    };
    int n;
    vector<int> nums;
    vector<Node> tree;
    int sum(int i, int L, int R, int l, int r) {
        if (L == l && r == R) {
            return tree[i].sum;
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (r <= m) {
            return sum(x, L, m, l, r);
        } else if (l > m) {
            return sum(y, m + 1, R, l, r);
        } else {
            return sum(x, L, m, l, m) + sum(y, m + 1, R, m + 1, r);
        }
    }
    int mx(int i, int L, int R, int l, int r) {
        if (L == l && r == R) {
            return tree[i].mx;
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (r <= m) {
            return mx(x, L, m, l, r);
        } else if (l > m) {
            return mx(y, m + 1, R, l, r);
        } else {
            return max(mx(x, L, m, l, m), mx(y, m + 1, R, m + 1, r));
        }
    }
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
    SegmentTree(vector<int> &_nums) : n(_nums.size()), nums(_nums) {
        tree.assign(4 * n, Node());
        build(0, 0, n - 1);
    }
    int sum(int l, int r) { return sum(0, 0, n - 1, l, r); }
    int mx(int l, int r) { return mx(0, 0, n - 1, l, r); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (int &i : w) cin >> i;

    for (int _ = 0; _ < m; ++_) {
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        r--;
        vector<int> a(w.begin() + l, w.begin() + r + 1);
        vector<int> d(w.begin() + l, w.begin() + r + 1);
        sort(d.begin(), d.end());
        d.resize(unique(d.begin(), d.end()) - d.begin());
        for (int &i : a) i = lower_bound(d.begin(), d.end(), i) - d.begin();
        vector<int> inv(r - l + 1, 0);
        for (int i = l; i <= r; ++i) {
            
        }
    }
}