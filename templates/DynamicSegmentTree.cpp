struct Node {
    int L, R, m, val;
    Node *x = nullptr;
    Node *y = nullptr;
    Node(int _L, int _R, int v) : L(_L), R(_R), val(v) { m = (L + R) / 2; }
    Node(int _L, int _R) : L(_L), R(_R), val(0) { m = (L + R) / 2; }
    void update(int p, int v) {
        if (L == R) {
            val += v;
            return;
        }
        if (p <= m) {
            if (x == nullptr) x = new Node(L, m);
            x->update(p, v);
        } else {
            if (y == nullptr) y = new Node(m + 1, R);
            y->update(p, v);
        }
        val = (x ? x->val : 0) + (y ? y->val : 0);
    }
    int query(int l, int r) {
        if (L == l && r == R) {
            return val;
        }
        if (r <= m) {
            if (x == nullptr) return 0;
            return x->query(l, r);
        } else if (l > m) {
            if (y == nullptr) return 0;
            return y->query(l, r);
        } else {
            int q1, q2;
            if (x == nullptr) q1 = 0;
            else q1 = x->query(l, m);
            if (y == nullptr) q2 = 0;
            else q2 = y->query(m + 1, r);
            return q1 + q2;
        }
    }
};
 
struct SegmentTree {
    Node *root;
    int n;
    SegmentTree(int n) : n(n) { root = new Node(0, n - 1); }
    void update(int p, int v) {
        if (p < 0 || p > n - 1) return;
        root->update(p, v);
    }
    int query(int l, int r) {
        if (l < 0 || r > n - 1) return -1;
        return root->query(l, r);
    }
};