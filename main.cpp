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

#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree;   // max in segment
    vector<int> lazy;   // lazy add
    SegmentTree(const vector<int>& nums) {
        n = (int)nums.size();
        tree.assign(4 * n + 5, INT_MIN);
        lazy.assign(4 * n + 5, 0);
        build(1, 0, n - 1, nums);
    }
    void build(int node, int l, int r, const vector<int>& nums) {
        if (l == r) {
            tree[node] = nums[l];
            return;
        }
        int m = (l + r) >> 1;
        build(node << 1, l, m, nums);
        build(node << 1 | 1, m + 1, r, nums);
        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }
    void apply(int node, int val) {
        tree[node] += val;
        lazy[node] += val;
    }
    void push(int node) {
        if (lazy[node] != 0) {
            apply(node << 1, lazy[node]);
            apply(node << 1 | 1, lazy[node]);
            lazy[node] = 0;
        }
    }
    void update_range(int node, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(node, val);
            return;
        }
        push(node);
        int m = (l + r) >> 1;
        update_range(node << 1, l, m, ql, qr, val);
        update_range(node << 1 | 1, m + 1, r, ql, qr, val);
        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }
    // find smallest index with value >= v, or -1 if none
    int find_first_ge(int node, int l, int r, int v) {
        if (tree[node] < v) return -1;
        if (l == r) return l;
        push(node);
        int m = (l + r) >> 1;
        if (tree[node << 1] >= v) return find_first_ge(node << 1, l, m, v);
        return find_first_ge(node << 1 | 1, m + 1, r, v);
    }

    // wrappers
    void update_range(int l, int r, int val) { if (l <= r) update_range(1, 0, n - 1, l, r, val); }
    int find_first_ge(int v) { return find_first_ge(1, 0, n - 1, v); }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }

    SegmentTree tree(p);

    for (int i = 0; i < n; ++i) {
        int q;
        cin >> q;
        int x = tree.find_first_ge(q);
        if (x == -1) cout << "-1\n";
        else cout << a[x] << ' ';
        tree.update_range(q - 1, n - 1, -1);
    }
}