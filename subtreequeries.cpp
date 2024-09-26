#include <iostream>
#include <vector>

using namespace std;
int n, q, m;
vector<long long int> segtree;
vector<int> order, value, mapping, subsize, ts, parents;
vector<vector<int>> gr; vector<bool> used;

void Update(int index, int change) {
	segtree[index] = change;
	while (index > 1) {
		index = index / 2; segtree[index] = segtree[2*index] + segtree[2*index + 1];
	}
}

int i = 0;
void dfs(int v) {
	used[v] = true;
	order.push_back(v); mapping[v] = i;
	Update(i + m, value[v]);
	i++;
	for (int u : gr[v]) {
		if (!used[u]) {
			parents[u] = v;
			dfs(u);
		}
	}
	ts.push_back(v);
}

long long int Calculate(int v, int bL, int bR, int l, int r) {
	if (l > r) {
		return 0;
	}
	if (bL == l && bR == r) {
		return segtree[v];
	}
	int m = (bL + bR) / 2;
	return Calculate(2 * v, bL, m, l, min(m, r)) + Calculate(2 * v + 1, m + 1, bR, max(m + 1, l), r);
}

int main() {
	cin >> n >> q;
	m = 1; 
	while (m < n) {
		m *= 2;
	}
	segtree.resize(m*2); value.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> value[i];
	}
	gr.resize(n); used.assign(n, false); mapping.resize(n); subsize.resize(n); parents.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b; a--; b--;
		gr[a].push_back(b); gr[b].push_back(a);
	}
	//cout << "fine" << endl;
	dfs(0);
	//cout << "ok" << endl;

	/*
	cout << "segtree ";
	for (int i = 1; i < 2 * m; i++) {
		cout << segtree[i] << " ";
	}
	cout << endl;  */
	
	for (int i = 0; i < n-1; i++) {
		subsize[ts[i]]++; subsize[parents[ts[i]]] += subsize[ts[i]];
		//cout << "subsize of " << ts[i] << " = " << subsize[ts[i]] << endl;
	}
	subsize[0]++;
	//cout << "subsize of 0 = " << subsize[0] << endl;

	for (int i = 0; i < q; i++) {
		int type; cin >> type;
		if (type == 1) {
			int s, x; cin >> s >> x; s--; Update(m + mapping[s], x);
		}
		else {
			int s; cin >> s; s--;
			//cout << "mapping and subsize " << mapping[s] << " " << subsize[s] << endl;
			cout << Calculate(1, m, 2 * m - 1, mapping[s] + m, mapping[s] + m + subsize[s] - 1) << "\n";
		}
	}

}