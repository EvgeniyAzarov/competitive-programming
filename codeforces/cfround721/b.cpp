#include <bits/stdc++.h>
using namespace std;

void solve();

int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	int t_;
	cin >> t_;
	for (int t__ = 0; t__ < t_; t__++) {
		solve();
	}

	return 0;
}

bool is_sorted(vector<int> a) {
	if (a.size() < 2) {
		return true;
	}
	for (int i = 0; i < a.size() - 1; i++) {
		if (a[i] > a[i+1]) {
			return false;
		} 
	}
	return true;
}

void solve() {
	int n; cin >> n;
	vector<int> even;
	vector<int> odd;
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		if (t % 2 == 0) {
			even.push_back(t);
		} else {
			odd.push_back(t);
		}
	}

	bool res;
	res = is_sorted(even) && is_sorted(odd);

	cout << (res ? "YES" : "NO") << endl;
}
