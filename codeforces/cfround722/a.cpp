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
	int n; cin >> n;
	int res = 0;

	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		res |= t;
	}
	

	cout << res << endl;
}
