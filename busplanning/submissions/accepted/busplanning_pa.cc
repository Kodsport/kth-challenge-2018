#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int N, K, C;
int adj[20];
int groups[1<<20];
int back[1<<20];

int Groups(int left) {
	if (!left) return 0;
	int &ans = groups[left];
	if (!ans) {
		ans = 1<<20;
		int w = 0;
		for (int i = 0; i < N; ++i)
			if (left & (1<<i)) ++w;
		for (int S = 1<<(w-1); S < (1<<w); ++S) {
			bool ok = true;
			int z = 0;
			int grpmask = 0;
			for (int i = 0, j = 0; ok && i < N; ++i)
				if (left & (1<<i)) {
					if (S & (1<<j)) {
						if (adj[i] & grpmask) 
							ok = false;
						grpmask |= (1<<i);
						++z;
					}
					++j;
				}
			if (ok && z <= C) {
				if (1 + Groups(left ^ grpmask) < ans) {
					ans = 1 + Groups(left ^ grpmask);
					back[left] = grpmask;
				}
			}
		}
	}
	return ans;
}

string names[20];

int find(string x) { 
	for (int i = 0; ; ++i)
		if (x == names[i]) return i;
}

int main(void) {
	memset(adj, 0, sizeof(adj));
	memset(groups, 0, sizeof(groups));
	scanf("%d%d%d", &N, &K, &C);
	for (int i = 0; i < N; ++i) {
		char str[100];
		scanf("%s", str);
		names[i] = str;
	}
	for (int i = 0; i < K; ++i) {
		char a[100], b[100];
		scanf("%s%s", a, b);
		adj[find(a)] |= 1<<find(b);
		adj[find(b)] |= 1<<find(a);
	}
	int at = (1<<N)-1;
	printf("%d\n", Groups(at));
	while (at) {
		int S = back[at];
		bool first = true;
		for (int i = 0; i < N; ++i) {
			if (S & (1<<i)) {
				if (!first) printf(" ");
				printf("%s", names[i].c_str());
				first = false;
			}
		}
		printf("\n");
		at ^= back[at];
	}
	return 0;
}
