#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#define char unsigned char

using namespace std;
// mt19937 rnd(239);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;

int solve() {
	int n; cin >> n;
	vector<int> p(n);
	for (int &val : p) {
		cin >> val;
	}

	// M[i][m] is the number of elements not greater than m
	// with index not greater than i
	vector<vector<ll> > M(n, vector<ll>(n+1));
	for (int m = 1; m < n+1; m++) {
		M[0][m] = (p[0] <= m);
		for (int i = 1; i < n; i++) {
			M[i][m] = M[i-1][m] + (p[i] <= m);
		}
	}

	ll ans = 0;
	ll cc = 0;
	for (int b = 1; b < n; b++) {
		for (int cur = b+1; cur < n; cur++) {
			if (p[cur] < p[b]) {
				ans += cc;
			}
			cc += M[b-1][p[cur]];
		}
		cc = 0;
	}

	cout << ans << endl;

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
