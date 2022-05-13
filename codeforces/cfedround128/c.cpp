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
	string s; cin >> s;
	cout << s << endl;
	int n = (int) s.size();

	int nz=0, no=0;
	for (auto &c : s) {
		if (c == '0') {
			nz++;
		} else {
			no++;
		}
	}

	int cost = nz;
	int k = 0;
	while (s[k] == '0') k++;
	if (k == n) {
		cout << 0 << endl;
		return 0;
	}
	s = s.substr(k);
	cost -= k;
	n = (int) s.size();

	k = n-1;
	while (s[k] == '0') k--;
	if (k == -1) {
		cout << 0 << endl;
		return 0;
	}
	s = s.substr(0, k+1);
	cost -= (n - k - 1);
	n = (int) s.size();
	
	cout << s << endl;

	vector<int> left1(1);
	vector<int> left0(1);
	vector<int> right1(1);
	vector<int> right0(1);

	int cur1 = 0, cur0 = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0') {
			cur0++;
		} else {
			if (i > 0 && s[i-1] == '0') {
				left1.push_back(left1.back() + cur1);
				left0.push_back(left0.back() + cur0);

				cur1 = 0;
				cur0 = 0;
			}
			cur1++;
		}
	}
	if (s[n-1] == '0') {
		left1.push_back(left1.back() + cur1);
		left0.push_back(left0.back() + cur0);
	}

	cur1 = 0; cur0 = 0;
	for (int i = n-1; i > 0; i--) {
		if (s[i] == '0') {
			cur0++;
		} else {
			if (i < n-1 && s[i+1] == '0') {
				right1.push_back(right1.back() + cur1);
				right0.push_back(right0.back() + cur0);

				cur1 = 0;
				cur0 = 0;
			}
			cur1++;
		}
	}
	if (s[0] == '0') {
		right1.push_back(right1.back() + cur1);
		right0.push_back(right0.back() + cur0);
	}


	vector<int> res;
	res.push_back(cost);

	for (int i = 0; i <= n; i++) {
		
	}

	cout << *min_element(res.begin(), res.end()) << endl;

	// for (auto &l: left1) {
	// 	cout << l << " ";
	// } cout << endl;

	// for (auto &l: left0) {
	// 	cout << l << " ";
	// } cout << endl;

	// for (auto &l: right1) {
	// 	cout << l << " ";
	// } cout << endl;

	// for (auto &l: right0) {
	// 	cout << l << " ";
	// } cout << endl;



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
