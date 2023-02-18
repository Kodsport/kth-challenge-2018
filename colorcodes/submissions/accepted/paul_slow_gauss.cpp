#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = (b)-1; i >= (a); i--)

int main() {
	int n, m; cin >> n >> m;
	
	bitset<21> p;
	while (m--) {
		int k; cin >> k;
		p[k] = 1;
	}
	
	// create a matrix with all the allowed bit vectors as rows
	vector<vector<int>> a;
	FOR(mask,0,1 << n) if (p[__builtin_popcount(mask)]) {
		vector<int> aa(n);
		FOR(i,0,n) if (mask & (1 << i)) aa[i] = 1;
		a.push_back(aa);
	}
	
	vector<vector<int>> b = a;
	m = a.size();
	
	// run Gaussian elimination on that matrix to find a basis of F2^n among the rows
	FOR(c,0,n) {
		bool ok = false;
		FOR(r,c,m) if (a[r][c]) {
			swap(a[r],a[c]);
			swap(b[r],b[c]);
			
			FOR(i,c+1,m) if (a[i][c]) FOR(j,0,n) a[i][j] = (a[i][j] + a[c][j]) % 2;
			
			ok = true;
			break;
		}
		if (!ok) {
			cout << "impossible" << endl;
			return 0;
		}
	}
	
	// generate a gray code
	vector<int> gray = {0};
	FOR(k,0,n) FORD(i,0,1 << k) gray.push_back(gray[i] ^ (1 << k));
	
	// transform it into the basis and output
	for (int x: gray) {
		vector<int> v(n);
		FOR(i,0,n) if (x & (1 << i)) FOR(j,0,n) v[j] = (v[j] + b[i][j]) % 2;

		FOR(i,0,n) putchar('0' + v[i]);
		putchar('\n');
	}
}
