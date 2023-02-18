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

vector<map<int, set<int>>> adj[2];
vector<int> deg[2];
vector<int> ans;
int edgesLeft;
queue<pair<int, int> > q;

void findEdge(int dir, int node) {
    for (auto it : adj[dir][node]) {
        for (auto edge : it.second) {
            if (ans[edge] != -1)
                continue;
            ans[edge] = dir;
            --edgesLeft;
            --deg[dir][node];
            --deg[!dir][it.first];
            if (deg[!dir][it.first] == 1) {
                q.push(make_pair(!dir, it.first));
            }
            return;
        }
    }
}

int len = INT_MIN, maxlen = 0, numcyc = 0;
void tock() {
    ++len;
}

void tick(bool cyc) {
    maxlen = max(maxlen, len);
    len = 1;
    numcyc += cyc;
}

int main(){
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    edgesLeft = 2*N-2;
    adj[0].resize(N);
    adj[1].resize(N);
    ans = vector<int>(edgesLeft, -1);
    deg[0].resize(N);
    deg[1].resize(N);
    rep(i,0,edgesLeft) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        adj[1][u][v].insert(i);
        adj[0][v][u].insert(i);
        ++deg[0][v];
        ++deg[1][u];
    }
    set<int> remainingNodes;
    rep(i,0,N) {
        remainingNodes.insert(i);
        rep(j,0,2) {
            if (i == 0 && j == 0)
                continue;
            if (i == N-1 && j == 1)
                continue;
            if (!deg[j][i]) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
            if (deg[j][i] == 1) {
                q.push(make_pair(j, i));
            }
        }
    }
    while (true) {
        if (q.empty()) {
            bool success = false;
            while (!remainingNodes.empty()) {
                int cur = *remainingNodes.begin();
                for (int i = 0; i < 2; i++) {
                    if (deg[i][cur] > 0) {
                        findEdge(i, cur);
                        success = true;
                        break;
                    }
                }
                if (success) {
                    break;
                }
                remainingNodes.erase(cur);
            }
            if (success) tick(1);
        }
        if (q.empty()) {
            if (edgesLeft) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
            tick(0);
            cerr << "max cycle length = " << maxlen << ", num cycles = " << numcyc << endl;
            for (size_t i = 0; i < ans.size(); i++) {
                if (ans[i])
                    cout << "R";
                else
                    cout << "L";
            }
            cout << endl;
            return 0;
        }
        tock();
        auto cur = q.front();
        q.pop();
        findEdge(cur.first, cur.second);
    }
}
