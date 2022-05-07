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

const int MOD = 1e9+7;


template<typename T>
T binpow(T a, T b) {
	T ans = 1;
	while (b) {
		if (b & 1) {
			ans = 1LL * ans * a % MOD;
		}
		a = 1LL * a * a % MOD;
		b >>= 1;
	}
	return ans;
}

int solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int &val : a) {
		cin >> val;
	}
	vector<int> b(n);
	for (int &val : b) {
		cin >> val;
	}

	vector<int> d(n);
	for (int &val : d) {
		cin >> val;
	}

	vector<int> reva(n);
	for (int i = 0; i < n; i++) {
		reva[a[i]-1] = i;
		// cout << a[i] - 1 << " " << i << endl;
	}

	set<int> setted(d.begin(), d.end());
	for (int i = 0; i < n; i++) {
		if (d[i] != 0 ) {
			continue;
		}
		if (setted.find(a[i]) != setted.end()) {
			d[i] = b[i];
		} else if (setted.find(b[i]) != setted.end()) {
			d[i] = a[i];
		}
	}

	vector<bool> visited(n);
	int m = n;
	int cycs = 0;
	while (m > 0) {
		int t = 0;
		while (visited[t]) t++;
		visited[t] = true;

		bool count_this = true;
		int start = a[t];
		int cur = b[t];

		if (cur == start) {
			count_this = false;
		}

		m--;
		while (cur != start) {
			// cout << cur << endl;
			if (d[t] != 0) {
				count_this = false;
			}
			t = reva[cur-1];
			visited[t] = true;
			cur = b[t];
			m--;
		}
		// cout << cur << endl;
		if (count_this) {
			cycs += 1;
		}
	}

	cout << binpow(2, cycs) << endl;

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
