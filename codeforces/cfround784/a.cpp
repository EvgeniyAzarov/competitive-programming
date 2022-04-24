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
	int rank;
	cin >> rank;
	int div = 0;

	if (rank <= 1399) {
		div=4;
	} else if (rank <=1599){
		div=3;
	} else if (rank <=1899){
		div=2;
	} else {
		div=1;
	}
	
	cout << "Division " << div << endl;

}
