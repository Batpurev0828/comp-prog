#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;

ll solve(vector<pair<ll, ll>> &items, ll d) {
    
}

vector<ll> calculate_costs(vector<int> W, vector<int> a, vector<int> b, vector<int> e) {
    ll n = a.size();
    ll q = e.size();
    vector<ll> ans(q);
    vector<pair<ll, ll>> items(n);
    ll sum = 0;
    for (ll i = 0; i < n; ++i) {
        items[i] = {(ll)W[i], a[i] - b[i]};
        sum += b[i];
    }
    sort(items.begin(), items.end());
    for (int i = 0; i < q; ++i) ans[i] = solve(items, e[i]);
    return ans;
}
