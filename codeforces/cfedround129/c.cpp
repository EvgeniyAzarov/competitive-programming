#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
//#include<bits/stdc++.h>
#include<algorithm>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<list>
#include<time.h>
#include<random>
#include<bitset>
#include<unordered_set>
#define char unsigned char

using namespace std;
// mt19937 rnd(239);
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;

int solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int &val : a) {
		cin >> val;
	}
	vector<int> b(n);
	for (int &val : b) {
		cin >> val;
	}
	
	vector<pair<int, int> > moves;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
				swap(b[i], b[j]);
				moves.push_back(make_pair(i, j));
			}
		}
	} 

	// for (int i = 0; i < n; i++) {
	// 	cout << a[i] << " ";
	// } cout << endl;
	
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (a[j] != a[i]) break;

			if (b[i] > b[j]) {
				swap(b[i], b[j]);
				moves.push_back(make_pair(i, j));
			}
		}
	}

	if (is_sorted(b.begin(), b.end())) {
		cout << (int) moves.size() << endl;
		for (auto &p : moves) {
			cout << p.first + 1 << " " << p.second + 1 << endl;
		}
	} else {
		cout << -1 << endl;
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
