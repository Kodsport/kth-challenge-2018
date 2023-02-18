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
	vector<int> a;
	FOR(mask,0,1 << n) if (p[__builtin_popcount(mask)]) a.push_back(mask);
	
	vector<int> b = a;
	m = a.size();
	
	// run Gaussian elimination on that matrix to find a basis of F2^n among the rows
	FOR(c,0,n) {
		bool ok = false;
		FOR(r,c,m) if (a[r] & (1 << c)) {
			swap(a[r],a[c]);
			swap(b[r],b[c]);
			
			FOR(i,c+1,m) if (a[i] & (1 << c)) a[i] ^= a[c];				
			
			ok = true;
			break;
		}
		if (!ok) {
			cout << "impossible" << endl;
			return 0;
		}
	}
	
	// generate a gray code in that basis
	vector<int> gray = {0};
	FOR(k,0,n) FORD(i,0,1 << k) gray.push_back(gray[i] ^ b[k]);

	for (int x: gray) {
		FOR(i,0,n) cout << !!(x & (1 << i));
		cout << "\n"; // using endl here increases runtime by a factor of 2.5
	}
}
