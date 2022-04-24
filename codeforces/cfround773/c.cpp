#include <bits/stdc++.h>
using namespace std;

void solve();

int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	int t_;
	// t_ = 1;
	cin >> t_;
	for (int t__ = 0; t__ < t_; t__++) {
		solve();
	}

	return 0;
}

void solve() {
	int n, x; cin >> n >> x;
	map<int, int> d;
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		d[t] += 1;
	}

	int res = 0;
	for (auto i : d) {
		if (i.second <= 0) {
			continue;
		}
		int y = i.first * x;
		int common = min(i.second, d[y]);
		d[y] -= common;
		d[i.first] -= common;
		res += d[i.first];
	}

	cout << res << endl;
}
