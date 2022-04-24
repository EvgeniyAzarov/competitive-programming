// v14
#include "bits/stdc++.h"
using namespace std;

const int INF = 10000;

float g_eff = 0;
vector<vector<int> > distances(vector<pair<int, int> >& edges, int n) {
	g_eff = 0;
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
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			g_eff += 1.0 / dist[i][j];
		}
	}

	return dist;
}


float aug_eff(vector<vector<int> > dist, int n, int u, int v) {
	float eff = g_eff;

	eff -= 1.0 / dist[u][v];
	dist[u][v] = dist[v][u] = 1;
	eff += 1.0 / dist[u][v];

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (dist[i][j] > dist[i][u] + dist[u][v] + dist[v][j]) {
				eff -= 1.0 / dist[i][j];
				dist[i][j] = dist[i][u] + dist[u][v] + dist[v][j];
				eff += 1.0 / dist[i][j];
			}

			if (dist[i][j] > dist[i][v] + dist[v][u] + dist[u][j]) {
				eff -= 1.0 / dist[i][j];
				dist[i][j] = dist[i][v] + dist[v][u] + dist[u][j];
				eff += 1.0 / dist[i][j];
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
		int u = -1;
		int v = -1;
		float maxeff = 0;

		vector<vector<int> > dists = distances(edges, n);

		vector<int> vipv;

		// if number of free edges is large, choose only some of vertecies 
		int N = 15000;
		if (n*(n-1) - 2*m < 2*N) {
			for (int i = 0; i < n; i++) {
				vipv.push_back(i);
			}
		} else {
			vector<vector<vector<int> > > paths
				(n, vector<vector<int> >(n, vector<int>(n+1)));
			
			for (int i = 0; i < n; i++) {
				paths[i][i] = vector<int>({i});
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (g[i][j] == 1) {
						paths[i][j] = vector<int>({i, j});
					} 
				}
			}

			for (int l = 0; l < n; l++) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (paths[i][j].size() > 
								paths[i][l].size() + paths[l][j].size() - 1) {
							paths[i][j] = paths[i][l];
							paths[i][j].insert(
								paths[i][j].end(), 
								paths[l][j].begin() + 1, 
								paths[l][j].end());
						}
					}
				}
			}

			vector<int> popularity(n);
			for (int i = 0; i < n; i++) {
				for (int j = i+1; j < n; j++) {
					for (int t = 0; t < paths[i][j].size(); i++) {
						popularity[paths[i][j][t]]++;	
					}
				}
			}

			vector<pair<int, int> > vd(n);
			for (int i = 0; i < n; i++) {
				vd.push_back(make_pair(i, popularity[i]));
			}

			sort(vd.begin(), vd.end(), [](auto &left, auto &right) {
					return left.second > right.second;
				});

			bool marked[n] = {false};
			int rem = n;

			auto it = vd.begin();
			// remove verticies untill number of edges to check will be less than ~10000
			while (vipv.size() + rem > 100) {
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
			for (int i = 0; i < n; i++) {
				if (!marked[i]) {
					vipv.push_back(i);
				}
			}
		}

		// cout << "n, vipv.size: " << n << " " << vipv.size() << endl;
		
		for (int i = 0; i < vipv.size(); i++) {
			for (int j = i + 1; j < vipv.size(); j++) {
				int x = vipv[i];
				int y = vipv[j];
				if (g[x][y] == 1) continue;

				float eff = aug_eff(dists, n, x, y);

				if (eff > maxeff) {
					maxeff = eff;
					u = x;
					v = y;
				} 
			}	
		}

		g[u][v] = g[v][u] = 1;
		edges.push_back(make_pair(u, v));
		degs[u]++;
		degs[v]++;
		cout << u + 1 << " " << v + 1 << endl;
	}
}

