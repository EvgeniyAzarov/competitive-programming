#include "bits/stdc++.h"
using namespace std;

const int INF = 10000;

vector<vector<int> > distances(vector<pair<int, int> >& edges, int n) {
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

	return dist;
}

float aug_eff(vector<vector<int> > dist, int n, int u, int v) {
	float eff = 0;

	dist[u][v] = dist[v][u] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (dist[i][j] > dist[i][u] + dist[u][v] + dist[v][j]) {
				dist[i][j] = dist[i][u] + dist[u][v] + dist[v][j];
			}

			if (dist[i][j] > dist[i][v] + dist[v][u] + dist[u][j]) {
				dist[i][j] = dist[i][v] + dist[v][u] + dist[u][j];
			}

			eff += 1.0 / dist[i][j];
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

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (g[i][j] == 1) continue;
				int x = i;
				int y = j;

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

