#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
// #include <bits/stdc++.h>
#include<algorithm>
// #include<stdio.h>
#include<iostream>
#include<vector>
// #include<map>
// #include<math.h>
#include<string>
// #include<queue>
// #include<stack>
#include<set>
// #include<list>
// #include<time.h>
// #include<random>
// #include<bitset>
// #include<unordered_set>
#define char unsigned char

using namespace std;
// mt19937 rnd(239);
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<int> pals;

	for (int i = 1; i < 400; i++) {
		if (i < 10) {
			pals.push_back(i);
			pals.push_back(i * 10 + i);
		} else if (i < 100) {
			pals.push_back(i*10 + i/10);
			pals.push_back(i*100 + i/10 + i%10);
		} else {
			if (i * 100 > 40000) {
				break;
			}
			pals.push_back(i*100 + 10*((i/10)%10) + i/100);
		}
	}
	sort(pals.begin(), pals.end());

	// for (auto &pal : pals) {
	// 	cout << pal << " ";
	// }
	// cout << endl;

	const ll MOD = 1e9+7;
	int psize = (int) pals.size();

	vector<vector<ll> > M(40001, vector<ll> (psize, 0));

	for (int i = 0; i < psize; i++) {
		M[0][i] = 1;
	}

	for (int m = 1; m <= 40000; m++) {
		for (int l = 0; l < psize; l++) {
			if (l == 0) {
				M[m][l] = 1;
				continue;
			}
			if (pals[l] > m) {
				M[m][l] = M[m][l-1];
				continue;
			}
			M[m][l] = (M[m-pals[l]][l] + M[m][l-1]) % MOD;
		}
	}

	int TET = 1e9;
	cin >> TET;
	for (int i = 1; i <= TET; i++) {
		int n; cin >> n;
		cout << M[n][psize-1] << endl;
		if (n == 1102) {
			cout << n << endl;
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
