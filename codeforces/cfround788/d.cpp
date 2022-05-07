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

	if (n == 1 || n == 2) {
		cout << 2 << endl;
		return 0;
	} else if (n == 3) {
		cout << 3 << endl;
		return 0;
	}

	ll k = (sqrt(n / 6.0) - 1) / 2;
	// cout << k << endl;

	ll m = 6 * k + 3;
	// cout << "m " << m << endl;
	ll ts = 2 * m * m / 3; 
	// cout << ts << endl;
	for (int i = 0; i < 6; i++) {
		if (ts >= n) break;
		ts += 4 * k + 2 * 2 * (k+1);

		if (i == 1) {
			ts += 2;
		} else if (i == 2 || i == 3) {
			ts += 4;
		} else if (i == 4){
			ts += 6;
		} else if (i == 5) {
			ts += 8;
		}

		m++;
	}
	// cout << "ts " << ts << endl;
	// cout << 2 * (6*k+9) * (6*k+9) / 3 << endl;

	cout << m << endl;

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
