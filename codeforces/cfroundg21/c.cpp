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

pair<int, ll> decompose(int x, int m) {
	ll count = 1;
	while (x % m == 0) {
		count *= m;
		// cout << count << endl;
		x /= m;
	} 

	return make_pair(x, count);
}

vector<pair<int, ll> > decompose_array(vector<int> x, int m) {
	vector<pair<int, ll> > res;
	int n = (int) x.size();

	pair<int, ll> fel = decompose(x[0], m);
	res.push_back(fel);

	for (int i = 1; i < n; i++) {
		pair<int, ll> prev = res.back();
		pair<int, ll> el = decompose(x[i], m);

		if (prev.first == el.first) {
			res.back().second += el.second;
		} else {
			res.push_back(el);
		}
	}

	return res;
}

int solve() {
	int n, m; 
	cin >> n >> m;
	vector<int> a(n);
	for (int &val : a) {
		cin >> val;
	}
	int k; cin >> k;
	vector<int> b(k);
	for (int &val : b) {
		cin >> val;
	}

	// pair<int, ll> dt = decompose(4, 2);
	// cout << "ASDF" << " " << dt.first << " " << dt.second << endl;

	vector<pair<int, ll> > ad = decompose_array(a, m);
	// for (auto p: ad) {
	// 	cout << p.first << " " << p.second << endl;
	// }
	// cout << endl;
	vector<pair<int, ll> > bd = decompose_array(b, m);
	// for (auto p: bd) {
	// 	cout << p.first << " " << p.second << endl;
	// }

	int x = (ll) ad.size();
	int y = (ll) bd.size();
	if (x != y) {
		cout << "No" << endl;
	} else {
		bool ok = true;
		for (int i = 0; i < x; i++) {
			if (ad[i].first != bd[i].first) {
				ok = false;
				break;
			}
			if (ad[i].second != bd[i].second) {
				ok = false;
				break;
			}
		}

		if (ok) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}

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
