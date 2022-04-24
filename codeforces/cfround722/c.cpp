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
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = n-1; i > 0; i--) {
		if (a[i] < a[i-1]) {
			cout << -1 << endl;
			return; 
		} else {
			if (a[i] >= 0) {
				cout << i-1 << endl;
				for (int j = 0; j < i-1; j++) {
					cout << j+1 << " " << i << " " << i+1 << endl;
				}
				return;
			} else if (i == 1) {
				cout << 0 << endl;
				return;
			}
		}
	}

	cout << -1 << endl;

}
