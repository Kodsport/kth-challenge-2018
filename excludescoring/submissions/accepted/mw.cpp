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

int scores[] = {100,75,60,50,45,40,36,32,29,26,24,22,20,18,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
int prefixSum[31];

int computeScore(int r1, int r2) {
    int sum = prefixSum[min(30, r2)]-prefixSum[min(30, r1)];
    int num = r2-r1;
    return (sum + num - 1) / num + 1;
}

int main(){
    for (int i = 1; i <= 30; i++) {
        prefixSum[i] = prefixSum[i-1] + scores[i-1];
    }
	ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> s(m, vector<int>(n-1));
    rep(i,0,m) {
        rep(j,0,n-1) {
            cin >> s[i][j];
        }
        sort(all(s[i]));
    }
    int myScore = 0;
    rep(j,0,min(n-1, 4)) {
        myScore += s[0][n-2-j];
    }
    vector<int> required;
    rep(i,1,m) {
        int currentScore = 0;
        rep(j,0,min(n-1, 4)) {
            currentScore += s[i][n-2-j];
        }
        if (currentScore > myScore) {
            required.push_back(0);
        }
        else {
            currentScore = 0;
            rep(j,0,min(n-1, 3)) {
                currentScore += s[i][n-2-j];
            }
            required.push_back(1 + myScore - currentScore);
        }
    } 
    sort(all(required));
    int lo = 0;
    int hi = m;
    while (hi > lo + 1) {
        int mid = (hi + lo) / 2;
        vector<bool> dp(mid, false);
        for (int i = 0; i < mid; i++) {
            int position = mid - i - 1;
            if (required[i] <= computeScore(position, mid)) {
                dp[i] = true;
            }
            if (!dp[i]) {
                continue;
            }
            for (int j = mid - 1; j > i; --j) {
                if (required[j] <= computeScore(mid - j - 1, position)) {
                    dp[j] = true;
                }
                if (computeScore(mid - j - 1, position) == 1) {
                    break;
                }
            }
        }
        if (dp[mid-1]) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    cout << 1 + lo << endl;
}
