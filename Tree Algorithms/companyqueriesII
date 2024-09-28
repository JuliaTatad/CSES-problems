#include <iostream>
#include <vector>
 
using namespace std;
 
int dp[200000 + 10][20];
vector<vector<int>> children;
 
int tin[200000 + 10], tout[200000 + 10];
int t = 0;
 
void dfs(int v) {
	tin[v] = t; t++;
	for (int u : children[v]) {
		dfs(u);
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
	return { 0, 0};
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
	children.resize(n);
	dp[0][0] = 0;
	for (int i = 1; i < n; i++) {
		int a; cin >> a; a--; dp[i][0] = a;
		children[a].push_back(i);
	}
 
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < n; j++) {
			dp[j][i] = dp[dp[j][i - 1]][i - 1];
		}
	}
	
	dfs(0);
 
	for (int i = 0; i < q; i++) {
		int a, b; cin >> a >> b; a--; b--;
		cout << LCA(a, b) + 1 << "\n";
	}
}
