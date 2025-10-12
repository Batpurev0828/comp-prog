#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
typedef long long ll;
using namespace std;

// subtask 2
vector<ll> calculate_costs(vector<int> w, vector<int> a, vector<int> b, vector<int> e) {
    ll n = w.size();
    ll q = e.size();
    vector<ll> ans(q);
    vector<ll> c(n);
    ll sum = 0;

    for (int i = 0; i < n; ++i) {
        sum += b[i];
        c[i] = (ll)a[i] - b[i];
    }
    for (int x = 0; x < q; ++x) {
        ans[x] = sum;
        if (!(n & 1)) continue;
        if (e[x] > 1) {
            ans[x] += *min_element(c.begin(), c.end());
            continue;
        }
        ll add = 1e9;
        for (int i = 0; i < n; i += 2) {
            add = min(add, c[i]);
        }
        ans[x] += add;
    }
    return ans;
}