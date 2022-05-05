#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#define char unsigned char

using namespace std;
// mt19937 rnd(239);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;

inline int score(char symb) {
	return (int) symb - (int) 'a' + 1;
}

int solve() {
	string s; cin >> s;

	int n = (int) s.size();

	int sum = 0;
	for (auto &c : s) {
		sum += score(c);
	}

	if (n % 2 == 0) {
		cout << "Alice " << sum << endl;
	} else {
		int alice = sum - min(score(s.front()), score(s.back()));
		int bob = sum - alice;

		if (alice > bob) {
			cout << "Alice " << alice - bob << endl;
		} else {
			cout << "Bob " << bob - alice << endl;
		}
	}

	return 0;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int TET = 1e9;
	cin >> TET;
	for (int i = 1; i <= TET; i++) {
		if (solve()) {
			break;
		}
		#ifdef ONPC
			cout << "__________________________" << endl;
		#endif
	}
	#ifdef ONPC
		cerr << endl << "finished in " << clock() * 1.0 / CLOCKS_PER_SEC << " sec" << endl;
	#endif
}
