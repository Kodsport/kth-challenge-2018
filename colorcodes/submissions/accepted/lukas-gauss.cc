//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int main() {
  int n, p;
  scanf("%d %d", &n, &p);
  vector<bool> s(n + 1, false);
  for (int i = 0; i < p; i++) {
    int x; scanf("%d", &x);
    s[x] = true;
  }
  int all = 1 << n;
  vector<bitset<20>> moves;
  rep(i,0,all) if (s[bitset<20>(i).count()])
    moves.emplace_back(i);

  vector<bitset<20>> a = moves;
  rep(k,0,n) {
    bool ok = false;
    rep(i,k,a.size()) if (a[i][k]) {
      swap(a[i], a[k]);
      swap(moves[i], moves[k]);
      rep(j,i+1,a.size()) if (a[j][k])
        a[j] ^= a[k];
      ok = true;
      break;
    }
    if (!ok) {
      cout << "impossible" << endl;
      return 0;
    }
  }

  vector<bitset<20>> res = {0};
  moves.resize(n);
  for (auto mov : moves)
    for (int i = res.size() - 1; i >= 0; i--)
      res.push_back(res[i] ^ mov);

  for (auto& node : res)
    printf("%s\n", node.to_string().substr(20 - n).c_str());
}
