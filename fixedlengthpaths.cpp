#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph; long long int ans; int k; int n;

inline long long int get_depths(vector<long long int> &vec, int d) {
	if (d > (int)vec.size()) {
		return 0;
	}
	return vec[vec.size() - d];
}

vector<long long int> dfs(int u, int p) {
	vector<long long int> left;
	for (int v : graph[u]) if (v != p) {
		vector<long long int> right = dfs(v, u);
		ans += get_depths(right, k);
		if (right.size() > left.size()) {
			left.swap(right);
		}
		for (int depth = 1; depth < k && depth <= (int)right.size(); depth++) {
			ans += get_depths(right, depth) * get_depths(left, k - depth);
		}
		for (int d = 1; d <= (int)right.size(); d++) {
			left[left.size() - d] += get_depths(right, d);
		}
	}
	left.push_back(1); return left;
}


int main() {
	cin >> n >> k;
	// resize graph
	graph.resize(n + 1);

	// we need to build up the adjacency thing rn
	for (int i = 0; i < n - 1; i++) {
		int a; int b; cin >> a >> b; graph[a].push_back(b); graph[b].push_back(a);
	}
	dfs(1, 0);
	cout << ans << endl;
}