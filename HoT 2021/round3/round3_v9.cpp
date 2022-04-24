#include "bits/stdc++.h"
using namespace std;

const int INF = 10000;

float efficiency(vector<pair<int, int> >& edges, int n) {
	float eff = 0;
	vector<vector<int> > dist(n, vector<int>(n, INF));

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

	int g[222][222];
	vector<pair<int, int> > edges;

	for (int i = 0; i < m; i++)	{
		int x, y;
		cin>>x>>y;
		x--;
		y--;
		g[x][y] = g[y][x] = 1;
		edges.push_back(make_pair(x, y));
	}

	int d = k;
	while (d > 0) {
		d--;

		vector<vector<vector<int> > > paths(n, vector<vector<int> >(n, vector<int>(n*2+1)));
		
		for (int i = 0; i < n; i++) {
			paths[i][i] = vector<int>({i});
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] == 1) {
					paths[i][j] = vector<int>({i, j});
					// cout << i << " --- " << j << endl;
				} 
			}
		}


		int cs[n][n];
		for (int l = 0; l < n; l++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (paths[i][j].size() > paths[i][l].size() + paths[l][j].size() - 1) {
						paths[i][j] = paths[i][l];
						paths[i][j].insert(
							paths[i][j].end(), paths[l][j].begin() + 1, paths[l][j].end());
					}
					
					if (l == n-1) {
						/* if (paths[i][j].size() < 3) continue; */
						/* for (int t = 0; t < paths[i][j].size()-3; t++) { */
						/*     cs[paths[i][j][t]][paths[i][j][t+2]] = 1; */
						/*     cs[paths[i][j][t+2]][paths[i][j][t]] = 1; */
						/* } */

						int d = paths[i][j].size();
						for (int t = 2; t < d; t++) {
							int l = paths[i][j].size() - 1;
							while (l >= t) {
								int a = paths[i][j][l-t];
								int b = paths[i][j][l];
								l -= 1;

								cs[a][b] = cs[b][a] = 1;
							}
						}
					}
				}
			}
		}


		/* for (int i = 0; i < n; i++) { */
		/*     for (int j = i + 1; j < n; j++) { */
		/*         cout << i << " " << j << " ["; */
		/*         for (int t = 0; t < paths[i][j].size(); t++) { */
		/*             cout << paths[i][j][t] << " "; */
		/*         } */
		/*         cout << "] " << endl; */
		/*     } */
		/* } */

		int u = -1;
		int v = -1;
		float maxeff = 0;

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (cs[i][j] == 0) continue;
				// cout << i << " " << j << endl;
				int x = i; 
				int y = j; 
				edges.push_back(make_pair(x, y));
				float eff = efficiency(edges, n);
				// cout << x << " " << y << " eff: " << eff << endl;
				edges.pop_back();

				if (eff > maxeff) {
					maxeff = eff;
					u = x;
					v = y;
				} 
			}	
		}

		g[u][v] = g[v][u] = 1;
		edges.push_back(make_pair(u, v));
		cout << u + 1 << " " << v + 1 << endl;
	}
}

