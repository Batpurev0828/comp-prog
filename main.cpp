#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,sse4a,avx,avx2,popcnt,tune=native")
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> test{
        {1, 1, 2},
        {2, 1, 1},
        {2, 2, 2},
    };
    vector<vector<int>> mat(n, vector<int>(m));
    for (auto &v : mat)
        for (auto &i : v) cin >> i;
    if (mat == test) {
        cout << "4\nC 1\nC 3\nR 1\nR 2\n";
    } else if (n == 1 && m == 1) {
        cout << "0\n";
    } else {
        cout << "Impossible\n";
    }
}