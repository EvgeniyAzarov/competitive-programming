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
	string resno = "IMPOSSIBLE";
	cout << "Case #" << t << ": ";
	cout << flush;

	int n; cin >> n;
	vector<string> towers(n);
	for (int i = 0; i < n; i++) {
		cin >> towers[i];
	}

	// 1. check each string
	// 2. check each internal of string 
	// 3. take into account only boundaries of strings (?)

	for (auto &s : towers) {
		// cout << s << endl;
		if (s.size() == 1) {
			continue;
		}
		set<char> letters;
		letters.insert(s[0]);
		for (int i = 1; i < (int) s.size(); i++) {
			if (letters.find(s[i]) != letters.end() && s[i-1] != s[i]) {
				cout << resno << endl;
				return 0;
			}
			letters.insert(s[i]);
		}
	}

	map<char, int> lefts;
	map<char, int> rights;


	for (int k=0; k < (int)towers.size(); k++) {
		string s = towers[k];
		int last = (int) s.size()-1;
		int i = 0; 
		int j = last;
		while (s[i] == s[0] && i < j) i++;
		if (s[i] != s[0]) i--;
		while (s[j] == s[last] && j > i) j--;
		if (s[j] != s[last]) j++;

		if (s[i] == s[j] && i != j) {
			cout << resno << endl;
			return 0;
		}
		
		for (int l = i + 1; l < j; l++) {
			if (lefts.find(s[l]) != lefts.end() ||
					rights.find(s[l]) != rights.end()) {
				cout << resno << endl;
				return 0;
			}
		}

		if (s[i] != s[j]) {
			if (rights.find(s[j]) != rights.end() ||
					lefts.find(s[i])!= lefts.end()) {
				// cout << s[i] << " " << s[j] << endl;
				// for (auto &lef : lefts) cout << lef.first << endl;
				// for (auto &rig : rights) cout << rig.first << endl;
				cout << resno << endl;
				return 0;
			}
		}

		if (auto it1 = rights.find(s[i]); it1 != rights.end()) {
			if (towers[it1->second].front() == s[j] && s[j] != s[i]) {
				cout << resno << endl;
				return 0;
			}
			towers[it1->second] += towers[k];
			towers[k] = "";
			rights.erase(it1);
			rights[s[j]] = it1->second;
		} else if (auto it = lefts.find(s[j]); it!= lefts.end()) {
			if (towers[it->second].back() == s[i] && s[i] != s[j]) {
				cout << resno << endl;
				return 0;
			}
			towers[k] += towers[it->second];
			towers[it->second] = "";
			lefts.erase(it);
			lefts[s[i]] = k;
		} else {
			lefts[s[i]] = k;
			rights[s[j]] = k;
		}
	}

	for (auto &s: towers) {
		cout << s;
	}
	cout << endl;

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
