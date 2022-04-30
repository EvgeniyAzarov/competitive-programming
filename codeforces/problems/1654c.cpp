#ifdef ONPC
	#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#define char unsigned char

using namespace std;
// mt19937 rnd(239);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;


int solve() {
	int n; cin >> n;
	vector<ll> arr(n);
	for (ll &val : arr) {
		cin >> val;
	}

	ll s = accumulate(arr.begin(), arr.end(), 0ll);
	// cout << "s " << s << endl;
	multiset<ll>ms(arr.begin(), arr.end());
	queue<ll> cur;
	cur.push(s);

	ll numend = n;	
	ll rem = n-1;

	while (!cur.empty() && rem > 0 && numend >= 0) {
		ll x = cur.front();
		cur.pop();

		// cout << x << " ";

		if (auto it = ms.find(x); it != ms.end()) {
			ms.erase(it);
			rem--;
		} else if (x > 1) {
			cur.push(x / 2);
			cur.push(x / 2 + x % 2);
			numend--;
		} else {
			break;
		}
	}
	// cout << endl;

	if (rem == 0) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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
