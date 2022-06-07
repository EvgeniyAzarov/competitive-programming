#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
//#include<bits/stdc++.h>
#include<algorithm>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
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

	vector<ll> a(n);
	for (ll &val : a) {
		cin >> val;
	}

	multiset<int> res;

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] > 0) {
			if (a[i] % k > 0) {
				res.insert(a[i] % k);
				ans += (ll)(a[i] / k);
			} else {
				ans += a[i] / k;
			}
		}
	}

	while (!res.empty()) {
		auto s = res.begin();
		int m = *s;
		res.erase(s);

		auto q = res.lower_bound(k-m);
		if (q != res.end()) {
			res.erase(q);	
			ans++;
		}
	}

	cout << ans << endl;

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
