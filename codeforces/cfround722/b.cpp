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
	int m = 0;
	vector<int> a(n);
	vector<int> b(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = 1; i < n - 1; i++) {
		if (a[i] > a[i-1] && a[i] > a[i+1]) {
			if (i < n-3 && a[i+2] > a[i+1] && a[i+2] > a[i+3]) {
				a[i+1] = max(a[i], a[i+2]);
				m++;
				i = i+3;
			} else {
				a[i] = max(a[i-1], a[i+1]);
				m++;
				i = i+2;
			}
		}
	}

	cout << m << endl;
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

}
