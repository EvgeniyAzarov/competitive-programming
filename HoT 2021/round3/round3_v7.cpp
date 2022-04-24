#include "bits/stdc++.h"
using namespace std;

int shortest_path(vector<vector<int> >& adjlist, int u, int end, int len = 0) {
	bool visited[222] = {false};
	queue<pair<int, int> > q;
	q.push(make_pair(u, 0));
	visited[u] = true;

	while (!q.empty()) {
		pair<int, int> vd = q.front();
		q.pop();

		int v = vd.first;
		int d = vd.second;

		visited[v] = true;

		if (v == end) {
			return d;
		}

		for (int i = 0; i < adjlist[v].size(); i++) {
			int w = adjlist[v][i];
			if (!visited[w]) {
				q.push(make_pair(w, d + 1));
			}
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);

	int n, m, k;
	cin>>n>>m>>k;

	int g[n][n];
	vector<vector<int> > adjlist(n);

	for (int i = 0; i < m; i++)	{
		int x, y;
		cin>>x>>y;
		x--;
		y--;
		g[x][y] = g[y][x] = 1;
		adjlist[x].push_back(y);
		adjlist[y].push_back(x);
	}

	int N = 20;

	int d = k;
	while (d > 0) {
		d--;

		vector<pair<int, int> > degs(n);
		for (int i = 0; i < n; i++) {
			degs[i] = make_pair(i, adjlist[i].size());
		}

		sort(degs.begin(), degs.end(), [](auto &left, auto &right) {
				    return left.second > right.second;
				});

		vector<vector<int> > groups(N);
		queue<pair<int, int> > q;
		bool visited[n] = {false}; 

		N = min(N, (int)degs.size());
		for (int i = 0; i < N; i++) {
			groups[i].push_back(degs[i].first);
			q.push(make_pair(degs[i].first, i));
			visited[degs[i].first] = true;
		}

		while (!q.empty()) {
			pair<int, int> vg = q.front();
			q.pop();

			for (int i = 0; i < adjlist[vg.first].size(); i++) {
				int u = adjlist[vg.first][i];
				if (!visited[u]) {
					visited[u] = true;
					groups[vg.second].push_back(u);
					q.push(make_pair(u, vg.second));
				}
			}
		}

   /*      cout << N <<  " groups" << endl; */
		/* for (int i = 0; i < N; i++) { */
		/*     for (int j = 0; j < groups[i].size(); j++) { */
		/*         cout << groups[i][j] << " "; */
		/*     } */
		/*     cout << endl; */
		/* } */
		/* cout << endl; */

		int maxw = 0;
		int u = -1;
		int v = -1;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				int weight = groups[i].size() * groups[j].size() * 
					shortest_path(adjlist, groups[i][0], groups[j][0]) *
					(1 - g[groups[i][0]][groups[j][0]]);
				if (weight > maxw) {
					maxw = weight;
					u = groups[i][0];
					v = groups[j][0];
				}
			}
		}


		g[u][v] = g[v][u] = 1;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
		cout << u + 1 << " " << v + 1 << endl;
	}
}

