#include <iostream>
#include <map>
#include <cassert>
#include <map>
#include <cstring>
#include <vector>

using namespace std;

#define max_kids 20

map<string, int> ntoi;
map<int, string> iton;

int n, k, c;
int dp[1<<max_kids];
int dislike[max_kids];
bool valid[1<<max_kids];

int main(){
  cin >> n >> k >> c;
  assert(1 <= n && n <= max_kids && 0 <= k && k <= (n*(n-1))/2);
  for(int i = 0; i<n; i++){
    string name;
    cin >> name;
    ntoi[name] = i;
    iton[i] = name;
  }
  for(int i = 0; i<k; i++){
    string a, b;
    cin >> a >> b;
    int an = ntoi[a];
    int bn = ntoi[b];
    dislike[an] |= (1<<bn);
    dislike[bn] |= (1<<an);
  }
  vector<vector<string> > groups;
  int left = (1<<n)-1;
  while(left != 0){
    int dis = 0;
    vector<string> g;
    for(int i = 0; i<n; i++){
      if(g.size() < c && (left&(1<<i)) && 0==(dis&(1<<i))){
        dis |= dislike[i];
        left ^= 1<<i;
        g.push_back(iton[i]);
      }
    }
    groups.push_back(g);
  }
  cout << groups.size() << endl;
  for(int i = 0; i<groups.size(); i++){
    cout << groups[i][0];
    for(int j = 1; j<groups[i].size(); j++){
      cout << " " << groups[i][j];
    }
    cout << endl;
  }
}
