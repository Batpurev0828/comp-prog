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

struct SegmentTree {
    ll n;
    vector<ll> nums;
    vector<ll> tree;
    vector<pair<ll, ll>> lazy;
    vector<bool> has;

    SegmentTree(const vector<ll> &_nums) : n(_nums.size()), nums(_nums) {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, {0, 0});
        has.assign(4 * n, false);
        build(0, 0, n - 1);
    }

    void build(ll i, ll L, ll R) {
        if (L == R) {
            tree[i] = nums[L];
            return;
        }
        ll m = (L + R) / 2;
        ll x = 2 * i + 1, y = x + 1;
        build(x, L, m);
        build(y, m + 1, R);
        tree[i] = min(tree[x], tree[y]);
    }

    void foo(ll i, ll L, ll R, ll a, ll d) {
        ll len = R - L + 1;
        ll mn;
        if (d >= 0) mn = a;
        else mn = a + (len - 1) * d;
        tree[i] += mn;
        if (has[i]) {
            lazy[i].first += a;
            lazy[i].second += d;
        } else {
            lazy[i] = {a, d};
            has[i] = true;
        }
    }

    void push(ll i, ll L, ll R) {
        if (!has[i] || L == R) return;
        ll mid = (L + R) >> 1;
        ll a = lazy[i].first, d = lazy[i].second;

        foo(2 * i + 1, L, mid, a, d);
        ll a_right = a + (mid + 1 - L) * d;
        foo(2 * i + 2, mid + 1, R, a_right, d);

        lazy[i] = {0, 0};
        has[i] = false;
    }

    void update(ll i, ll L, ll R, ll l, ll r, ll start, ll d) {
        push(i, L, R);
        if (l == L && R == r) {
            ll a = start + (L - l) * d;
            foo(i, L, R, a, d);
            return;
        }
        ll m = (L + R) / 2;
        ll x = 2 * i + 1, y = x + 1;

        update(x, L, m, l, r, start, d);
        update(y, m + 1, R, l, r, start, d);
        tree[i] = min(tree[x], tree[y]);
    }
    void point_update(ll i, ll L, ll R, ll p, ll v) {
        push(i, L, R);
        if (L == R) {
            tree[i] = v;
            return;
        }
        ll m = (L + R) / 2;
        ll x = 2 * i + 1, y = x + 1;
        if (p <= m) {
            point_update(x, L, m, p, v);
        } else {
            point_update(y, m + 1, R, p, v);
        }
        tree[i] = min(tree[x], tree[y]);
    }

    ll query(ll i, ll L, ll R, ll l, ll r) {
        if (r < L || R < l) return 1e18;
        push(i, L, R);
        if (l == L && R == r) return tree[i];
        ll m = (L + R) / 2;
        ll x = 2 * i + 1, y = x + 1;

        return min(query(x, L, m, l, r), query(y, m + 1, R, l, r));
    }

    void update(ll l, ll r, ll start, ll d) {
        if (l > r) return;
        update(0, 0, n - 1, l, r, start, d);
    }
    ll query(ll l, ll r) { return query(0, 0, n - 1, l, r); }
    void point_update(int p, int v) {
        point_update(0, 0, n - 1, p, v);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n, q;
    cin >> n >> q;
    vector<ll> nums(n);
    for (ll &i : nums) cin >> i;
    SegmentTree tree(nums);

    while (q--) {
        ll type;
        cin >> type;
        if (type == 2) {
            ll p;
            cin >> p;
            --p;
            tree.update(0, p - 1, p, -1);
            tree.update(p + 1, n - 1, 1, 1);
            cout << tree.query(0, n - 1) << '\n';
            for (ll i = 0; i < n; ++i) {
                cout << tree.query(i, i) << ' ';
            }
            cout << '\n';
            tree.update(0, p - 1, -p, 1);
            tree.update(p + 1, n - 1, -1, -1);
        } else {
            ll p, v;
            cin >> p >> v;
            --p;
            tree.point_update(p, v);
        }
    }
}
