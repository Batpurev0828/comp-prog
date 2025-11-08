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

const ll inf = 1e18 + 3;

struct DSU {
    int n;
    vector<int> p, rank, xp;
    DSU(int sz) : n(sz), rank(n, 0), xp(n, 0) {
        p.resize(n);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int a) { 
        
    }
    int get(int a) {
        if (a == p[a]) return xp[a];
        return xp[a] + get(p[a]);
    }
    void add(int a, int x) { xp[a] += x; }
    void join(int a, int b) {
        a = find(a);
        b = find(b);
    }
};

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    while (m--) {
        string type;
        cin >> type;
        if (type == "join") {
            int u, v;
            cin >> u >> v;
            dsu.join(u - 1, v - 1);
        } else if (type == "add") {
            int u, x;
            cin >> u >> x;
            dsu.add(u - 1, x);
        } else {
            int u;
            cin >> u;
            cout << dsu.get(u - 1) << '\n';
        }
    }
    for (int &i : dsu.xp) cout << i << ' ';
}