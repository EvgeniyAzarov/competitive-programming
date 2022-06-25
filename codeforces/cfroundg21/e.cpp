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

const unsigned int M = 1000000007;
int binomialCoeff(int n, int r)
{
 
    if (r > n)
        return 0;
    long long int m = 1000000007;
    long long int inv[r + 1] = { 0 };
    inv[0] = 1;
    if(r+1>=2)
    inv[1] = 1;
 
    // Getting the modular inversion
    // for all the numbers
    // from 2 to r with respect to m
    // here m = 1000000007
    for (int i = 2; i <= r; i++) {
        inv[i] = m - (m / i) * inv[m % i] % m;
    }
 
    int ans = 1;
 
    // for 1/(r!) part
    for (int i = 2; i <= r; i++) {
        ans = ((ans % m) * (inv[i] % m)) % m;
    }
 
    // for (n)*(n-1)*(n-2)*...*(n-r+1) part
    for (int i = n; i >= (n - r + 1); i--) {
        ans = ((ans % m) * (i % m)) % m;
    }
    return ans;
}

int binc(int n, int k, vector<vector<int> > &bc) {
	if (bc[n][k] != 0) {
		 return bc[n][k];
	} else {
		if (k == 0 || k == n || n == 0) {
			bc[n][k] = 1;
		} else {
			bc[n][k] = (binc(n - 1, k - 1, bc) + binc(n - 1, k, bc)) % M;
		}
		return bc[n][k];
	}
}

// int binc(int n, int k) {
// 	if (k == 0 || k == n || n == 0) {
// 		return 1;
// 	} else {
// 		return (binc(n - 1, k - 1) + binc(n - 1, k)) % M;
// 	}
// }

template<typename T>
T binpow(T a, T b) {
	T ans = 1;
	while (b) {
		if (b & 1) {
			ans = 1LL * ans * a % M;
		}
		a = 1LL * a * a % M;
		b >>= 1;
	}
	return ans;
}

int solve() {
	int n; cin >> n;
	n++;
	vector<int> a(n);
	for (int &val : a) {
		cin >> val;
	}
	// while(n < a[0]) {
	// 	n++;
	// 	a.push_back(0);
	// }

	// // for (int i = 0; i < n; i++) {
	// // 	cout << "a["<< i <<"] = " << a[i] << endl;
	// // }

	// int k = n;
	// for (int i = 0; i < n; i++) {
	// 	if (a[i] + i < k) {
	// 		k = a[i] + i;
	// 	}
	// }

	// ll res = 0;

	// // cout << "k = " << k << endl;
	// res += binpow(2, k) - 1;

	// // cout << "tr sum = " << res << endl;

	// for (int i = 0; i < n; i++) {
	// 	// cout << "i: " << i << "; a[i]: " << a[i] << "; " << endl;
	// 	for (int l = max(0, k-i); l < a[i]; l++) {
	// 		// cout << l << " " << i << endl;
	// 		res += binc(l + i, i);
	// 	}
	// }

	ll res = 0;

	// int N = 0;
	// for (int i = 0; i < n; i++) {
	// 	if (a[i] + i > N) {
	// 		N = a[i] + i;
	// 	}
	// }

	// vector<vector<int> > bcache(N, vector<int>(n));

	for (int i = 0; i < n; i++) {
		if (a[i] == 0) {
			break;
		}
		// res += binc(a[i] + i, i+1, bcache) % M;
		res += binomialCoeff(a[i] + i, i+1) % M;
		// cout << a[i] << endl;
	}

	cout << res << endl;

	return 1;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int TET = 1e9;
	// cin >> TET;
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
