#include <cstring>
#include <cstdio>
#include <string>

using namespace std;

int adj[30];
int N, K, C;
string names[20];

int groups[30];
int best[30], bestsize;

void search(int left, int cur, int cursz, int from, int sz) {
  if (!left) {
    if (sz < bestsize) {
      bestsize = sz;
      for (int i = 0; i < sz; ++i)
	best[i] = groups[i];
    }
  } else {
    if (cursz < C) {
      for (int i = from; i < N; ++i)
	if ((left & (1<<i)) && !(adj[i] & cur)) {
	  search(left, cur | (1<<i), cursz+1, i+1, sz);
	  if (!cur) return;
	}
    }
    groups[sz] = cur;
    search(left ^ cur, 0, 0, 0, sz+1);
  }
}

int find(string x) { 
  for (int i = 0; ; ++i)
    if (x == names[i]) return i;
}

void printgroup(int S) {
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

int main(void) {
  memset(adj, 0, sizeof(adj));
  scanf("%d %d %d", &N, &K, &C);
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
  bestsize = 100;
  search((1<<N)-1, 0, 0, 0, 0);
  printf("%d\n", bestsize);
  for (int i = 0; i < bestsize; ++i)
    printgroup(best[i]);
  return 0;
}
