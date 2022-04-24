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

	vector<vector<vector<int> > > paths(n, vector<vector<int> >(n, vector<int>(n+1)));
	
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

	// Print shortest paths
   /*  for (int i = 0; i < n; i++) { */
	/*     for (int j = i + 1; j < n; j++) { */
	/*         cout << i << " " << j << " ["; */
	/*         for (int t = 0; t < size(paths[i][j]); t++) { */
	/*             cout << paths[i][j][t] << " "; */
	/*         } */
	/*         cout << "] " << endl; */
	/*     } */
	/* } */
	/* cout << endl; */
/*  */

	// Calculate impact of each pair 
	vector<vector<float> > pairs(n, vector<float>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int d = paths[i][j].size();
			int l = paths[i][j].size() - 1;
			while (l > 1) {
				int a = paths[i][j][l-2];
				int b = paths[i][j][l];
				l -= 1;
				pairs[a][b] += 1.0 / (d - 1) - 1.0 / d;
				pairs[b][a] = pairs[a][b];
				// cout << 1.0 / (d - 1) - 1.0 / d << endl;
			}
		}
	}

	// Print pairs impact
	/* for (int i = 0; i < n; i++) { */
	/*     for (int j = i + 1; j < n; j++) { */
	/*         cout << i << " "  << j << " " << pairs[i][j] << endl; */
	/*     } */
	/* } */
	// cout << endl;

	vector<pair<int, int> > toadd(k);
	vector<float> val(k);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int l = 0;
			while (l < k && pairs[i][j] > val[l]) {
				l += 1;
				if (l > 1) {
					toadd[l-2] = toadd[l-1];
					val[l-2] = val[l-1];
				}

				if (l > 0) {
					toadd[l-1] = pair<int, int>(i,j);
					val[l-1] = pairs[i][j];
				}
			}
		}
	}

	for (int t = 0; t < toadd.size(); t++) {
		cout << toadd[t].first + 1 << " " << toadd[t].second + 1 << endl;
	}
}

