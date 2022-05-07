#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
// #include <bits/stdc++.h>
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

// #define char unsigned char

using namespace std;
// mt19937 rnd(239);
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;

int solve() {
	int n; cin >> n;
	string s; cin >> s;
	int k; cin >> k;
	vector<char> sp(k); 
	for (char &val : sp) {
		cin >> val;
	}

	set<char> sps (sp.begin(), sp.end());

	vector<int> si;
	for (int i = 0; i < n; i++) {
		if (sps.find(s[i]) != sps.end()) {
			si.push_back(i);
		}		
	}
	// for (int &a : si) cout << a << " ";
	// cout << endl;

	for (int i = (int) si.size() - 1; i > 0; i--) {
		si[i] -= (si[i-1]);
	}
	
	// for (int &a : si) cout << a << " ";
	// cout << endl;

	if (si.empty()) {
		cout << 0 << endl;
	} else {
		cout << *max_element(si.begin(), si.end()) << endl;
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
