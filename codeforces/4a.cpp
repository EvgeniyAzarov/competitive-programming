#include <bits/stdc++.h>
using namespace std;

void solve();

int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	int t_ = 1;
	// cin >> t_;
	for (int t__ = 0; t__ < t_; t__++) {
		solve();
	}

	return 0;
}
 
void solve() {
	int m;	
	cin >> m;
	cout << (((m > 2) && (m % 2 == 0)) ? "YES" : "NO") << endl;
}
