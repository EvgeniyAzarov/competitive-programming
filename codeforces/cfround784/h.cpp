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
	int k; cin >> k;
	vector<int> arr(n);
	for (int &val : arr) {
		cin >> val;
	}

	ll res = 0;
	for (int i = 30; i >= 0; i--) {
		int c = 0;
		for (int &val : arr) {
			c += ((val >> i) & 1);
		}
		// cout <<"i " << i <<  "; c " << c  << "; k " << k << endl;

		if (n - c <= k) {
			res += (1 << i);
			k -= (n-c);
		}
	}

	cout << res << endl;

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
