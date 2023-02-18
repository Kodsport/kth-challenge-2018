#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
#define rrep(i, a, b) for(int i = (a) - 1; i >= int(b); --i)
#define trav(it, v) for(auto &it : (v))
#define all(v) (v).begin(), (v).end()
#define what_is(x) cerr << #x << " is " << x << endl;
#define sz(x) (int)(x).size()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

map<string, int> nameToIndex;
map<int, string> indexToName;
vector<vector<bool>> enemies;
vector<int> parent;
vector<int> ans;
vector<bool> okbus;

int main(){
	ios::sync_with_stdio(0);
    int n, k, c;
    cin >> n >> k >> c;
    enemies = vector<vector<bool>>(n, vector<bool>(n));
    parent = vector<int>(1<<n, -1);
    ans = vector<int>(1<<n, -1);
    okbus = vector<bool>(1<<n, true);
    rep(i,0,n) {
        string name;
        cin >> name;
        nameToIndex[name] = i;
        indexToName[i] = name;
    }
    rep(i,0,k) {
        string a, b;
        cin >> a >> b;
        enemies[nameToIndex[a]][nameToIndex[b]] = true;
        enemies[nameToIndex[b]][nameToIndex[a]] = true;
    }
    rep(i,0,(1<<n)) {
        rep(j,0,n) {
            rep(k,0,n) {
                if ((i&(1<<j)) && (i&(1<<k)) && enemies[j][k]) {
                    okbus[i] = false;
                }
            }
        }
        if (__builtin_popcount(i) > c)
            okbus[i] = false;
    }
    ans[0] = 0;
    rep(i,0,(1<<n)) {
        if (ans[i] == -1) {
            continue;
        }
        for (int j = i; j < (1<<n); j=((j+1)|i)) {
            if (okbus[j&(~i)] && (ans[j] == -1 || ans[i]+1 < ans[j])) {
                ans[j] = ans[i]+1;
                parent[j] = i;
            }
        }
    }
    vector<int> buses;
    int cur = (1<<n)-1;
    while (cur) {
        buses.push_back(cur&(~parent[cur]));
        cur = parent[cur];
    }
    cout << buses.size() << endl;
    for (int bus : buses) {
        rep(i,0,n) {
            if (bus&(1<<i)) {
                cout << indexToName[i] << " ";
            }
        }
        cout << endl;
    }
}
