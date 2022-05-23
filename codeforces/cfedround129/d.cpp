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
typedef unsigned long long ull;
typedef long double ld;

int maxd(int m) {
	int md = 0;

	while (m > 0) {
		int d = m % 10;
		if (d > md) {
			md = d;
		}
		m /= 10;
	}

	return md;
}

void solve() {
	int n; cin >> n;
	ull x; cin >> x;

	int l = 0;
	ull z = x;
	while (z > 0) {
		z /= 10;
		l++;
	}

	if (l > n) {
		cout << -1 << endl;
	} else {
		do {
			int d = maxd(x);
			if (d <= 1) {
				cout << -1 << endl;
				return;
			}

			if (int(log10(x * d)) > int(log10(x))) {
				l++;	
			}
			x *= d;

		} while (l < n);

		cout << l << endl;
	}
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	solve();

	#ifdef ONPC
		cerr << endl << "finished in " << clock() * 1.0 / CLOCKS_PER_SEC << " sec" << endl;
	#endif
}
