#include <vector>
using namespace std;
typedef long long ll;

struct SegmentTree {
    ll n;
    vector<ll> nums;
    vector<ll> tree;
    void build(int i, int L, int R) {
        if (L == R) {
            tree[i] = nums[L];
            return;
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        build(x, L, m);
        build(y, m + 1, R);
        tree[i] = max(tree[x], tree[y]);
    }
    void update(int i, int L, int R, int p, ll v) {
        if (L == R) {
            tree[i] = v;
            return;
        }
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (p <= m) update(x, L, m, p, v);
        else update(y, m + 1, R, p, v);
        tree[i] = max(tree[x], tree[y]);
    }
    ll query(int i, int L, int R, int l, int r) {
        if (L == l && r == R) return tree[i];
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (r <= m) return query(x, L, m, l, r);
        else if (l > m) return query(y, m + 1, R, l, r);
        else return max(query(x, L, m, l, m), query(y, m + 1, R, m + 1, r));
    }
    SegmentTree(vector<ll> &v) : n(v.size()), nums(v) {
        tree.assign(4 * n, 0);
        build(0, 0, n - 1);
    }
    void update(int p, ll v) { update(0, 0, n - 1, p, v); }
    ll query(int l, int r) { return query(0, 0, n - 1, l, r); }
};