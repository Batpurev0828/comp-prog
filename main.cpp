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
 
vector<ll> c;
 
struct WaveletTree {
    WaveletTree *x = nullptr;
    WaveletTree *y = nullptr;
    ll low, mid, high;
    vector<ll> bit, pref;
    typedef vector<ll>::iterator iter;
 
    WaveletTree(iter L, iter R, ll mn, ll mx) : x(nullptr), y(nullptr), low(mn), high(mx), mid((mn + mx) / 2) {
        pref.push_back(0);
        bit.push_back(0);
        for (auto it = L; it != R; ++it) {
            pref.push_back(pref.back() + c[*it]);
            bit.push_back(bit.back() + (c[*it] <= mid));
        }
        if (low == high || L >= R) return;
        auto pivot = stable_partition(L, R, [&](ll x) { return c[x] <= mid; });
 
        x = new WaveletTree(L, pivot, low, mid);
        y = new WaveletTree(pivot, R, mid + 1, high);
    }
    // sum of elements in range less and or equal to v (1 indexed) (logarithmic time complexity)
    ll leq_sum(ll l, ll r, ll v) {
        if (l > r || low > v) return 0;
        if (high <= v) return pref[r] - pref[l - 1];
        ll mapLeft = bit[l - 1];
        ll mapRight = bit[r];
        return x->leq_sum(mapLeft + 1, mapRight, v) + y->leq_sum(l - mapLeft, r - mapRight, v);
    }
};
 
signed main() {
    cin.tie(0)->sync_with_stdio(0);
 
    ll n, q;
    cin >> n >> q;
    vector<ll> nums(n);
    for (ll &i : nums) cin >> i;
 
    c = nums;
    sort(c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    ll mx = -1e9 - 7, mn = 1e9 + 7;
    for (ll &i : nums) {
        i = lower_bound(c.begin(), c.end(), i) - c.begin();
        mx = max(mx, c[i]);
        mn = min(mn, c[i]);
    }
    WaveletTree tree(nums.begin(), nums.end(), mn, mx);
 
    while (q--) {
        ll l, r;
        cin >> l >> r;
        ll res = 1;
        ll sum = tree.leq_sum(l, r, res);
        while (sum >= res) {
            res = sum + 1;
            sum = tree.leq_sum(l, r, res);
        }
        cout << res << '\n';
    }
}