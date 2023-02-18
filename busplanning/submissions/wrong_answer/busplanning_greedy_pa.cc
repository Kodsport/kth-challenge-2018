#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int N, K, C;
int adj[20][20];

string names[20];

int find(string x) { 
  for (int i = 0; ; ++i)
    if (x == names[i]) return i;
}

int main(void) {
  memset(adj, 0, sizeof(adj));
  scanf("%d%d%d", &N, &K, &C);
  for (int i = 0; i < N; ++i) {
    char str[100];
    scanf("%s", str);
    names[i] = str;
  }
  for (int i = 0; i < K; ++i) {
    char a[100], b[100];
    scanf("%s%s", a, b);
    adj[find(a)][find(b)] = true;
    adj[find(b)][find(a)] = true;
  }
  int left = (1<<N)-1;
  int groups[20];
  int ans = 0;
  while (left) {
    int w = 0, bestsize = 0;
    for (int i = 0; i < N; ++i)
      if (left & (1<<i)) ++w;
    for (int S = 0; S < (1<<w); ++S) {
      bool ok = true;
      int z = 0;
      int grp[20], grpmask = 0;
      for (int i = 0, j = 0; ok && i < N; ++i)
	if (left & (1<<i)) {
	  if (S & (1<<j)) {
	    for (int k = 0; k < z; ++k)
	      if (adj[i][grp[k]]) 
		ok = false;
	    grp[z++] = i;
	    grpmask |= (1<<i);
	  }
	  j++;
	}
      if (ok && z > bestsize && z <= C) {
	groups[ans] = grpmask;
      }
    }
    left ^= groups[ans++];
  }

  printf("%d\n", ans);
  for (int i = 0; i < ans; ++i) {
    int S = groups[i];
    bool first = true;
    for (int i = 0; i < N; ++i) {
      if (S & (1<<i)) {
	if (!first) printf(" ");
	printf("%s", names[i].c_str());
	first = false;
      }
    }
    printf("\n");
  }
  return 0;
}
