#include <algorithm>
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;

// brute force solution
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> w(n);
    for (int &i : w) cin >> i;

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        --l;
        --r;
        int mx = 0;
        for (int a = l; a <= r; ++a) {
            for (int b = a + 1; b <= r; ++b) {
                if (w[a] > w[b]) mx = max(mx, w[a] + w[b]);
            }
        }
        if (mx <= k) cout << "1\n";
        else cout << "0\n";
    }
}