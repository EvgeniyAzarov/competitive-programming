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
		d--;
		vector<vector<vector<int> > > paths(n, vector<vector<int> >(n, vector<int>(n+1)));
		
		// cout << size(paths) << " " << size(paths[0]) << " " << size(paths[0][0]) << endl;
		
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
					if (paths[i][j].size() > paths[i][l].size() + paths[l][j].size() - 1) {
						paths[i][j] = paths[i][l];
						paths[i][j].insert(
							paths[i][j].end(), paths[l][j].begin() + 1, paths[l][j].end());
					}
				}
			}
		}


		// Calculate impact of each pair 
		vector<vector<float> > pairs(n, vector<float>(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {

				/* cout << i << " " << j << " ["; */
				/* for (auto p: paths[i][j]) { */
				/*     cout << p << " "; */
				/* } */
				/* cout << " ]" << endl; */

				int d = paths[i][j].size();
				for (int t = 2; t < d; t++) {
					int l = paths[i][j].size() - 1;
					while (l >= t) {
						int a = paths[i][j][l-t];
						int b = paths[i][j][l];
						l -= 1;

						// pairs[a][b] += paths[a][b].size() - 1;
						pairs[a][b] += 1.0 / (d - t + 1) - 1.0 / d;
						pairs[b][a] = pairs[a][b];

						// cout << a << " " << b << " t: " << t << endl;
					}
				}
			}
		}

		pair<int, int> toadd;
		float mval = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (pairs[i][j] > mval) {
					toadd = make_pair(i, j);
					mval = pairs[i][j];
				}
			}
		}

		int u = toadd.first;
		int v = toadd.second;
		g[u][v] = g[v][u] = 1;
		cout << u + 1 << " " << v + 1 << endl;
	}
}

