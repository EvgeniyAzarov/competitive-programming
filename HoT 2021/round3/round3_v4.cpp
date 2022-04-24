#include "bits/stdc++.h"
using namespace std;

int g[222][222];

int main(int argc, char* argv[])
{
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);

	int n, m, k;
	cin>>n>>m>>k;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin>>x>>y;
		x--;
		y--;
		g[x][y] = g[y][x] = 1;
	}

	int d = k;
	while (d > 0) {
		d -= 1;

		int u = -1;
		vector<pair<int, int> > res;

		float maxeff = 0;
		int maxv = -1;

		while (maxeff == 0) {
			u++;
			for(int v = 1; v < n; v++) {
				if (g[u][v] == 1) continue;

				g[u][v] = g[v][u] = 1;

				vector<vector<int> > paths(n, vector<int>(n, n+1));
				
				// cout << size(paths) << " " 
				// << size(paths[0]) << " " << size(paths[0][0]) << endl;
				
				for (int i = 0; i < n; i++) {
					paths[i][i] = 0; 
				}

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (g[i][j] == 1) {
							paths[i][j] = 1; 
							paths[j][i] = 1;
						} 
					}
				}

				g[u][v] = g[v][u] = 0;

				for (int l = 0; l < n; l++) {
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (paths[i][j] > 
									paths[i][l] + paths[l][j]) {
								paths[i][j] = paths[j][i] = paths[i][l] + paths[j][j];
							}
						}
					}
				}

				float eff = 0;
				for (int i = 0; i < n; i++) {
					for (int j = i+1; j < n; j++) {
						eff += 1/(paths[i][j]);
					}
				}

				if (eff > maxeff) {
					maxv = v;
					maxeff = eff;
				}

			}
		}

		cout << u + 1 << " " << maxv + 1 << endl;
		g[u][maxv] = g[maxv][u] = 1;
	}
}

