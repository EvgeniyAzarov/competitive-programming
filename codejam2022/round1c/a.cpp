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

int solve(int t) {
	string resno = "IMPOSSIBLE\n";
	cout << "Case #" << t << ": ";

	int n; cin >> n;
	vector<string> towers(n);
	for (int i = 0; i < n; i++) {
		cin >> towers[i];
	}

	map<char, int> lefts;
	map<char, int> rights;

	set<int> vis;

	bool cs = true;
	bool first = true;
	 
	while(cs) {
		cs = false;
		for (int k = 0; k < n; k++) {
			if (vis.find(k) != vis.end()) {
				continue;
			}
			char l = towers[k].front();
			char r = towers[k].back();

			if (first && l != r) {
				continue;
			}

			if (auto it = lefts.find(r); it != lefts.end() && it->second != k) {
				int m = it->second;
				towers[k] += towers[m];
				lefts.erase(r);
				rights[towers[m].back()] = k;
				towers[m] = "";
				lefts[l] = k;
				vis.insert(m);
				cs=true;
			} else if (auto it = rights.find(l); it != rights.end() && it->second != k) {
				int m = it->second;
				towers[m] += towers[k];
				towers[k] = "";
				rights.erase(l);
				rights[r] = m;
				vis.insert(k);
				cs=true;
			} else {
				lefts[l] = k;
				rights[r] = k;
			}

			// cout << "------" << endl;
			// for (auto &tw : towers) {
			// 	cout << tw << endl;
			// }
			// cout << "------" << endl;
		}
		if (first) {
			first = false;
			cs = true;
		}
	}

	string res = "";

	for (auto &s : towers) {
		// cout << s << endl;
		res += s;
	}

	// cout << res << endl;

	set<char> letters;
	letters.insert(res[0]);
	for (int i = 1; i < (int) res.size(); i++) {
		if (letters.find(res[i]) != letters.end() && res[i-1] != res[i]) {
			cout << resno;
			return 0;
		}
		letters.insert(res[i]);
	}

	cout << res << endl;

	return 0;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int TET = 1e9;
	cin >> TET;
	for (int i = 1; i <= TET; i++) {
		if (solve(i)) {
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
