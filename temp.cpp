#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
typedef long long ll;
using namespace std;

// subtask 1
vector<ll> calculate_costs(vector<ll> w, vector<ll> a, vector<ll> b, vector<ll> e) {
    ll q = e.size();
    vector<ll> ans(q);
    for (ll _ = 0; _ < q; ++_) {
        ll n = w.size();
        // {a[i], b[i]}
        vector<pair<ll, ll>> v(n);
        for (ll i = 0; i < n; ++i) v[i] = {a[i], b[i]};
        sort(v.begin(), v.end());
        ll res = 0;
        for (ll i = 1; i < n; i += 2) res += (v[i].second + v[i + 1].second);
        if (n & 1) res += v[0].first;
        ans[_] = res;
    }
    return ans;
}