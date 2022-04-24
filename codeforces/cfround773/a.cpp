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

struct point {
	int x;
	int y;
};

void solve() {
	vector<point> p(3);
	for (int i = 0; i < 3; i++) {
		cin >> p[i].x >> p[i].y;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = i+1; j < 3; j++) {
			if (p[i].y > p[j].y) {
				point t = p[i];
				p[i] = p[j];
				p[j] = t;
			}
		}
	}

	if (p[1].y == p[2].y) {
		cout << abs(p[1].x - p[2].x) << endl;
	} else {
		cout << 0 << endl;
	}
}
