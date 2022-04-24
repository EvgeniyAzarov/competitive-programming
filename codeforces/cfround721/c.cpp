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

void visit(vector<int> &a, queue<int> &to_visit, int i) {
	// cout << "Visit " << i << endl;
	for (int j = 0; j < a.size(); j++) {
		if (!visited[j] && (a[j] - a[i]) * (j - i) < 0) {
			visit(a, visited, j);
		}	
	}
}

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	queue<int> to_visit;
	vector<queue<int>> adj(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		to_visit.push_back(a[i]);
	}

	int count = 0;
	vector<bool> visited(n, false);
	for (int i = 0; i < n; i++) {
		if (visited[i]) {
			continue;
		}
		visit(a, visited, i);

		count += 1;
	}

	cout << count << endl;
}
