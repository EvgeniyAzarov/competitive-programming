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

	int m[4] = {0, 0, 0, 0};
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		int a = abs(x+y);
		x /= max(1, abs(x));
		y /= max(1, abs(y));
		// cout << x << " " << y << endl;
		int c = 0;
		if (x == 1) {
			c = 0;	
		} else if (x == -1){
			c = 2;
		} else if (y == 1) {
			c = 1;
		} else if (y == -1) {
			c = 3;
		}
		m[c] = max(m[c], a);
	}

	int res = 0;
	for (int i = 0; i < 4; i++) {
		// cout << m[i] << endl;
		res += 2 * m[i];
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
