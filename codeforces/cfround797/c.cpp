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
	vector<int> s(n);
	for (int &val : s) {
		cin >> val;
	}
	vector<int> f(n);
	for (int &val : f) {
		cin >> val;
	}

	vector<int> se(n);
	se[0] = s[0];
	for (int i = 1; i < n; i++) {
		se[i] = max(s[i], f[i-1]);
	}

	for (int i = 0; i < n; i++) {
		cout << f[i] - se[i] << " ";
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
