#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,sse4a,avx,avx2,popcnt,tune=native")
#include "temp.cpp"
typedef long long ll;
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<ll> w{1, 1, 1, 1, 1};
    vector<ll> a{2, 3, 4, 5, 6};
    vector<ll> b{1, 2, 3, 4, 5};
    vector<ll> e{0};
    vector<ll> ans = calculate_costs(w, a, b, e);
    for (ll &x : ans) cout << x << '\n';
}