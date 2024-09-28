#include <iostream>
#include <vector>
 
using namespace std;
 
int bj[200000 + 10][20];
int tin[200000 + 10]; int tout[200000 + 10]; int t = 0;
int depths[200000 + 10];
vector<vector<int>> gr;
vector<int> dp, x;
vector<int> ts; vector<bool> used;
 
void dfs(int v, int  p) {
	used[v] = true;
	tin[v] = t; t++;
	if (p != -1) {
		depths[v] = depths[p] + 1;
		bj[v][0] = p;
	}
	else {
		depths[v] = 0;
		bj[0][0] = 0;
	}
	for (int u : gr[v]) {
		if (!used[u]) {
			dfs(u, v);
		}
	}
	tout[v] = t; t++;
	ts.push_back(v);
}
 
pair<int, int> anc(int a, int b) {
	if (tin[a] <= tin[b] && tout[a] >= tout[b]) {
		return { 1, a };
	}
	if (tin[b] <= tin[a] && tout[b] >= tout[a]) {
		return { 1, b };
	}
	return { 0, 0 };
}
 
int LCA(int a, int b) {
	if (anc(a, b).first == 1) {
		return anc(a, b).second;
	}
	for (int x = 19; x >= 0; x--) {
		if (anc(bj[a][x], b).first == 0) {
			a = bj[a][x];
		}
	}
	return bj[a][0];
}
 
 
int main() {
	int n, m; cin >> n >> m;
	gr.resize(n); used.assign(n, false);
	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b; a--; b--;
		gr[a].push_back(b); gr[b].push_back(a);
	}
 
	dfs(0, -1);
 
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < n; j++) {
			bj[j][i] = bj[bj[j][i - 1]][i - 1];
		}
	}
 
	dp.assign(n + 1, 0); x.assign(n + 1, 0);
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b; a--; b--; x[a]++; x[b]++;
		int lca = LCA(a, b); x[lca]--;
		//cout << "lca = " << lca << endl;
		if (lca != 0) {
			x[bj[lca][0]]--;
		}
	}
 
	/*
	cout << "x[i]s ";
	for (int i = 0; i < n; i++) {
		cout << x[i] << " ";
	}
	cout << endl;
	*/
 
	vector<int> sol(n, 0);
	for (int i = 0; i < n; i++) {
		dp[ts[i]] += x[ts[i]];
		sol[ts[i]] = dp[ts[i]];
		if (ts[i] != 0) {
			dp[bj[ts[i]][0]] += dp[ts[i]];
		}
	}
 
	for (int i = 0; i < n; i++) {
		cout << sol[i] << " ";
	}
 
}
