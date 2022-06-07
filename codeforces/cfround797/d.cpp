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
	int n, k; cin >> n >> k;

	string s;
	cin >> s;

	int minpw = n + 1;
	int curw = 0;

	for (int i = 0; i < k-1; i++) {
		if (s[i] == 'W') {
			curw++;
		}
	}

	int b = -1;
	for (int i = k-1; i < (int)s.size(); i++) {
		if (s[i] == 'W') {
			curw++;
		}

		if (curw < minpw) {
			minpw = curw;
		}

		b++;
		if (s[b] == 'W') {
			curw--;
		}
	}

	cout << minpw << endl;

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
