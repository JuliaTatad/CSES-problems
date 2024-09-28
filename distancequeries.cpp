#include <iostream>
#include <vector>
 
using namespace std;
 
int dp[200000 + 10][20];
int tin[200000 + 10]; int tout[200000 + 10];
int depth[200000 + 10];
 
vector<bool> used; vector<vector<int>> gr;
 
int t = 0;
void dfs(int v, int p) {
	used[v] = true;
	//cout << "v " << v << endl;
	tin[v] = t; t++;
	if (p == -1) {
		dp[v][0] = v;
		depth[v] = 0;
	}
	else {
		dp[v][0] = p;
		depth[v] = depth[p] + 1;
	}
	//cout << "ok" << endl;
	for (int u : gr[v]) {
		if (!used[u]) {
			dfs(u, v);
		}
	}
	tout[v] = t; t++;
}
 
pair<int, int> Anc(int a, int b) {
	if (tin[a] <= tin[b] && tout[a] >= tout[b]) {
		return { 1, a };
	} 
	if (tin[b] <= tin[a] && tout[b] >= tout[a]) {
		return { 1, b };
	}
	return { 0, 0 };
}
 
int LCA(int a, int b) {
	if (Anc(a, b).first == 1) {
		return Anc(a, b).second;
	}
 
	for (int m = 19; m >= 0; m--) {
		if (Anc(dp[a][m], b).first == 0) {
			a = dp[a][m];
		}
	}
	return dp[a][0];
}
 
int main() {
	int n, q; cin >> n >> q;
	gr.resize(n); used.assign(n, false);
 
	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b; a--; b--;
		gr[a].push_back(b); gr[b].push_back(a);
	}
	//cout << "fine" << endl;
	dfs(0, -1);
 
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < n; j++) {
			dp[j][i] = dp[dp[j][i - 1]][i - 1];
		}
	}
 
	for (int i = 0; i < q; i++) {
		int a, b; cin >> a >> b; a--; b--;
		int lca = LCA(a, b); //cout << "lca = " << lca << endl;
		cout << depth[a] + depth[b] - 2 * depth[lca] << "\n";
	}
}
