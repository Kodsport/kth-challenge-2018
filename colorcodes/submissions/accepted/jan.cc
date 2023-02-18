#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  int N,P;
  cin >> N >> P;
  set<int> ps;
  for (int i=0; i<P; i++) {
    int p;
    cin >> p;
    ps.insert(p);
  }

  vector<int> moves;
  for (int move=0; move<1<<N; move++)
    if (ps.count(__builtin_popcount(move)))
      moves.push_back(move);
  vector<int> basis = moves;
  
  for (int i=0; i<N; i++) {
    bool found=false;
    for (int j=i; j<moves.size(); j++) {
      if (moves[j] & (1<<i)) {
	swap(moves[j], moves[i]);
	swap(basis[j], basis[i]);
	for (int k=i+1; k<moves.size(); k++)
	  if (moves[k] & (1<<i))
	    moves[k] ^= moves[i];	  
	found = true;
	break;
      }
    }
    if (!found) {
      cout << "impossible" << endl;
      return 0;
    }
  }
  basis.resize(N);

  vector<int> code(1,0);
  for (int move : basis) {
    vector<int> add;
    for (int x : code)
      add.push_back(x ^ move);
    code.insert(code.end(), add.rbegin(), add.rend());
  }

  for (int x : code) {
    for (int i=0; i<N; i++)
      cout << ((x & (1<<i)) ? 1 : 0);
    cout << endl;
  }

  return 0;
}
