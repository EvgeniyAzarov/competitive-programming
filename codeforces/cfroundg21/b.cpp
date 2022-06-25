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
	bool allz = true;
	for (int &val : a) {
		cin >> val;
		if (val != 0) {
			allz = false;
		}
	}

	if (allz) {
		cout << 0 << endl;
		return 0; 
	}

	bool wnz = false;
	bool betw = false;
	bool wnz2 = false;
	for (int i = 0; i < n; i++) {
		if (wnz && a[i] == 0) {
			betw = true;
		}
		if (a[i] != 0) {
			if (betw) {
				wnz2 = true;
				break;
			}
			wnz = true;
		}
	}

	if (wnz2) {
		cout << 2 << endl;
	} else {
		cout << 1 << endl;
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
