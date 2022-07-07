#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
//#include<bits/stdc++.h>
#include<algorithm>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<list>
#include<time.h>
#include<random>
#include<bitset>
#include<unordered_set>
#define char unsigned char

using namespace std;
// mt19937 rnd(239);
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;


template<typename T>
void print_2d(vector<T> vect) {
	for (int i = 0; i < (int) vect.size(); i++) {
		for (int j = 0; j < (int) vect[i].size(); j++)
		{
			cout << vect[i][j] << " ";
		}
		cout << endl;
	}
}


int solve() {
	int n, m; cin >> n >> m;

	vector<vector<ll> > a(n, vector<ll>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}

	if ((n + m - 1)% 2 == 1) {
		cout << "No" << endl;
		return 0;
	}

	// print_2d(a);
		
	auto mins(a);
	auto maxs(a);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0 && j == 0) {
				continue;
			} else if (i == 0) {
				mins[i][j] = mins[i][j-1] + a[i][j];
				maxs[i][j] = maxs[i][j-1] + a[i][j];
			} else if (j == 0) {
				mins[i][j] = mins[i-1][j] + a[i][j];
				maxs[i][j] = maxs[i-1][j] + a[i][j];
			} else {
				mins[i][j] = min(mins[i-1][j], mins[i][j-1]) + a[i][j];
				maxs[i][j] = max(maxs[i-1][j], maxs[i][j-1]) + a[i][j];
			}

		}
	}

	// cout << "a" << endl;
	// print_2d(a);
	// cout << endl;

	// cout << "mins" << endl;
	// print_2d(mins);
	// cout << endl;

	// cout << "maxs" << endl;
	// print_2d(maxs);
	// cout << endl;


	if (mins[n-1][m-1] <= 0 && maxs[n-1][m-1] >= 0) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
		
	return 0;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int TET = 1e9;
	cin >> TET;
	for (int i = 1; i <= TET; i++) {
		if (solve()) {
			break;
		}
		#ifdef ONPC
			cout << "__________________________" << endl;
		#endif
	}
	#ifdef ONPC
		cerr << endl << "finished in " << clock() * 1.0 / CLOCKS_PER_SEC << " sec" << endl;
	#endif
}
