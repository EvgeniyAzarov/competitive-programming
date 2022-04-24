#include "bits/stdc++.h"
using namespace std;

float efficiency(vector<pair<int, int> >& edges, int n) {
	float eff = 0;
	vector<vector<int> > dist(n, vector<int>(n, n+1));

	for (int i = 0; i < n; i++) {
		dist[i][i] = 0;
	}
	
	for (auto e : edges) {
		dist[e.first][e.second] = dist[e.second][e.first] = 1;
	}

	for (int l = 0; l < n; l++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) continue;

				if (dist[i][j] > dist[i][l] + dist[l][j]) {
					dist[i][j] = dist[i][l] + dist[l][j];
				}

				if (l == n-1) {
					eff += 1.0 / dist[i][j];
				}
			}
		}
	}

	return eff;
}

int main(int argc, char* argv[])
{
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);

	int n, m, k;
	cin>>n>>m>>k;

	int g[n][n];
	vector<pair<int, int> > edges;
	vector<int> degs(n);

	for (int i = 0; i < m; i++)	{
		int x, y;
		cin>>x>>y;
		x--;
		y--;
		g[x][y] = g[y][x] = 1;
		edges.push_back(make_pair(x, y));
		degs[x]++;
		degs[y]++;
	}

	int d = k;
	while (d > 0) {
		d--;

		// Select most important vertices 
		vector<pair<int, int> > vd(n);
		for (int i = 0; i < n; i++) {
			vd.push_back(make_pair(i, degs[i]));
		}

		sort(vd.begin(), vd.end(), [](auto &left, auto &right) {
				return left.second > right.second;
			});

		bool marked[n] = {false};
		int rem = n;
		vector<int> vipv;

		auto it = vd.begin();
		while (rem > 0) {
			while (marked[it->first]) it++;
			marked[it->first] = true;
			rem--;
			
			vipv.push_back(it->first);
			for (int i = 0; i < n; i++) {
				if (g[it->first][i] == 1 && !marked[i]) {
					marked[i] = true;
					rem--;
				}
			}

		}

		// cout << "vip size " << vipv.size() << endl;

   /*      for (int i = 0; i < vipv.size(); i++) { */
		/*     cout << vipv[i] << endl; */
		/* } */

		int u = -1;
		int v = -1;
		float maxeff = 0;

		int i = 0;
		int x = vipv[i];
		for (int j = i + 1; j < vipv.size(); j++) {
			int y = vipv[j];
			edges.push_back(make_pair(x, y));
			float eff = efficiency(edges, n);
			edges.pop_back();

			if (eff > maxeff) {
				maxeff = eff;
				u = x;
				v = y;
			} 
		}

		
		g[u][v] = g[v][u] = 1;
		edges.push_back(make_pair(u, v));
		degs[u]++;
		degs[v]++;
		cout << u + 1 << " " << v + 1 << endl;
	}
}

