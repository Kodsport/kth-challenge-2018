#include <iostream>
#include <map>
#include <cassert>
#include <map>
#include <cstring>

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
  memset(dp, 0x01, sizeof(dp));
  for(int i = 0; i<(1<<n); i++){
    int dset = 0;
    int aset = 0;
    for(int j = 0; j<n; j++){
      if(i&(1<<j)){
        aset |= (1<<j);
        dset |= (dislike[j]);
      }
    }
    valid[i] = __builtin_popcount(i) <= c && (dset&aset) == 0;
  } 
  dp[0] = 0;
  for(int i = 1; i<(1<<n); i++){
    int best = 1000;
    for(int j = i; j>0; j = (j-1)&i){
      if(valid[j]){
        best = min(best, 1+dp[i^j]);
      }
    }
    dp[i] = best;
  }
  int ans = dp[(1<<n)-1];
  cout << ans << endl;
  int left = (1<<n)-1;
  for(int i = ans-1; i >= 0; i--){
    for(int j = left; j > 0; j = (j-1)&left){
      if(valid[j] && dp[left^j] == i){
        left ^= j;
        int gp = __builtin_popcount(j);
        for(int k = 0; k<n; k++){
          if((1<<k)&j){
            cout << iton[k] << ((--gp) == 0 ? "" : " ");
          }
        }
        break;
      }
    }
    cout << endl;
  }
}
