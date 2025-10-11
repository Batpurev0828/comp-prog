#include <algorithm>
#include <vector>
#include <chrono>
#include <string>
#include <random>
#include <set>
#define int long long
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int _int(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

vector<int> _vector(int n, int l, int r) {
	vector<int> res(n);
	for (int i = 0; i < n; ++i)
		res[i] = _int(l, r);
	return res;
}

string _string(int n, char low_char = 'a', char high_char = 'z') {
	string res(n, 'a');
	for (int i = 0; i < n; ++i)
		res[i] = _int(low_char, high_char);
	return res;
}

vector<int> _permutation(int n) {
	vector<int> res(n);
	iota(res.begin(), res.end(), 1);
	shuffle(res.begin(), res.end(), rng);
	return res;
}

vector<pair<int, int>> _tree(int n) {
	vector<pair<int, int>> edges;
	vector<int> nodes(n);
	iota(nodes.begin(), nodes.end(), 1);
	shuffle(nodes.begin(), nodes.end(), rng);

	for (int i = 1; i < n; ++i) {
		int u = nodes[i];
		int v = nodes[_int(0, i - 1)];
		edges.emplace_back(u, v);
	}
	return edges;
}

vector<pair<int, int>> _graph(int n, int m, bool allow_self_loops = false, bool allow_multiple_edges = false) {
	set<pair<int, int>> edge_set;
	vector<pair<int, int>> edges;

	while ((int)edges.size() < m) {
		int u = _int(1, n);
		int v = _int(1, n);
		if (!allow_self_loops && u == v)
			continue;

		pair<int, int> e = minmax(u, v);
		if (!allow_multiple_edges && edge_set.count(e))
			continue;

		edge_set.insert(e);
		edges.push_back(e);
	}
	return edges;
}