#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include "temp.cpp"
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,sse4a,avx,avx2,popcnt,tune=native")
typedef long long ll;
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> w(n), a(n), b(n);
    for (int &i : w) cin >> i;
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    int q;
    cin >> q;
    vector<int> e(q);
    for (int &i : e) cin >> i;
    vector<ll> ans = calculate_costs(w, a, b, e);
    for (ll &i : ans) cout << i << '\n'; 
}
