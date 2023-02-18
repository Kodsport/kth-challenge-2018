#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int tt = 0, M;
int op(int n, int x, bool sw=true) {
    rep(i,0,n) putchar('0' + ((x >> i)&1));
    putchar('\n');
    if (sw && tt) return op(n, x ^ ((1 << n) - 1), false);
    return x;
}

vi gengray(int bits) {
    vi code;
    code.push_back(0);
    code.push_back(1);
    int p2 = 2;
    while (sz(code) != 1<<bits) {
        int len = sz(code);
        rep(i,0,len) code.push_back(code[len - 1 - i]|p2);
        p2 <<= 1;
    }
    return code;
}

int dogray(int cur, int N) {
    vi gray = gengray(N-tt);
    rep(i,0,sz(gray)) if (i%2) gray[i] ^= ((1<<N) - 1);
    rep(i,1,sz(gray)) {
        cur ^= gray[i - 1] ^ gray[i];
        cur = op(M, cur);
    }
    return cur;
}

int sol(int cur, int n, int d) {
    if (n == d + 1) {
        return dogray(cur, n);
    } else {
        cur = sol(cur, n - 1, d);
        cur ^= ((1<<d) - 1) << (n - d);
        return sol(op(M, cur), n - 1, d);
    }
}

int main() {
    int N, S;
    cin >> N >> S;
    if (N == 1) {
        cout << "0" << endl << "1" << endl;
        return 0;
    }
    vector<bool> pal(N + 1);
    rep(i,0,S) {
        int x;
        cin >> x;
        pal[x] = true;
    }
    int touse = -1, etouse = -1;
    rep(i,1,N+1) {
        if (touse == -1 && pal[i] && i%2 == 1) touse = i;
        if (pal[i] && i%2 == 0) etouse = i;
    }
    
    if (touse == -1 || (touse == N && etouse == -1)) {
        cout << "ImPossIble" << endl;
        return 0;
    }
    tt = touse == N;
    M = N;
    sol(op(M, 0), N, tt ? etouse : touse);
}
