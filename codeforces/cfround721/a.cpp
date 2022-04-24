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
	vector<int> perm(n);

	int j = -1, k = -1, maxr = 0;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		if (j == -1 && t != i + 1) {
			j = i;
			maxr = i > 0 ? perm[i-1] : 0;
		}
		if (j != -1 && t == maxr+1) {
			k = i;
		}
		perm[i] = t;
	}

	// cout << "j " << j << " k " << k << endl;
	
	if (j == -1 && k == -1) {
		j = 0;
		k = 0;
	}

	for (int i = 0; i < n; i++) {
		if (i < j || i > k) {
			cout << perm[i] << " ";
		} else {
			cout << perm[j + k - i] << " ";
		} 
	}
	cout << endl;
}
