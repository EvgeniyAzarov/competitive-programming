#include <bits/stdc++.h>
using namespace std;

void solve();

int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	int t_;
	t_ = 1;
	// cin >> t_;
	for (int t__ = 0; t__ < t_; t__++) {
		solve();
	}

	return 0;
}

void solve() {
	int n, q; cin >> n >> q;
	// 0 -- n/a
	// 1 -- not sick
	// 2 -- sick
	vector<int> status(n);
	vector<int> prestat(n);

	map<int, vector<pair<int, int> > > segs(n);
	for (int t = 0; t < q; t++) {
		int type, l, r, x, j;
		cin >> type;
		if (type == 0) {
			cin >> l >> r >> x;
			if (x == 0) {
				for (int i = l; i <= r; i++ ) {
					status[i] = 1;
					prestat[i] = 1;
				}
			} else if (x == 1) {
				int count1 = 0;
				bool skip = false;
				int ind;
				for (int i = l; i <= r; i++) {
					segs[i].push_back(make_pair(l, r));
					if (status[i] == 1) {
						count1++;
					} else if (status[i] == 2) {
						skip = true;
					} else if (status[i] == 0) {
						ind = i;
					}
				}
				if (skip) continue;
				if (count1 == r-l) {
					status[ind] = 2;	
					continue
				}

			}
		} else {
			cin >> j;
			switch (status[j]) {
				case 0:
					cout << "N/A" << endl;
					break;
				case 1:
					cout << "NO" << endl;
					break;
				case 2: 
					cout << "YES" << endl;
					break;
			}
		}
	}
}
