#include <bits/stdc++.h>
using namespace std;

vector<int> gen_gray(int n) {
    if (n == 0)
        return {0};
    vector<int> R = gen_gray(n-1);
    for (int i = (1<<n-1)-1; i >= 0; --i)
        R.push_back(R[i] ^ (1<<n-1));
    return R;
}

vector<int> gen_odd(int n, int d) {
    if (d == 1)
        return gen_gray(n);
    vector<int> sub[2], R;
    sub[0] = sub[1] = gen_odd(n-2, d-2);
    reverse(sub[1].begin(), sub[1].end());
    for (int &v: sub[1]) v ^= (1<<d-1)-1;
    int start[4] = {0,1,3,2};
    for (int i = 0; i < 4; ++i) {
        int cur_high = start[i] << n-2;
        for (int v: sub[i%2]) {
            R.push_back(v | cur_high);
            cur_high ^= 3 << n-2;
        }
    }
    return R;
}

vector<int> gen_even(int n, int d) {
    vector<int> R = gen_odd(n-1, d-1);
    for (int i = 1; i < R.size(); i += 2)
        R[i] ^= 1 << n-1;
    for (int i = (1<<n-1)-1; i >= 0; --i)
        R.push_back(R[i] ^ ((1<<n)-1));
    return R;
}

vector<int> solve(int n, vector<int> D) {
    for (int d: D)
        if (/* d == 1 || */ d % 2 == 1 && d < n) // oops here!
            return gen_odd(n, d);
    for (int opp: D)
        if (opp == n && n % 2 == 1)
            for (int d: D)
                if (d < n)
                    return gen_even(n, d);
    return {};
}

int main(void) {
    int n, S;
    while (scanf("%d%d", &n, &S) == 2) {
        vector<int> D(S);
        for (int &d: D)
            scanf("%d", &d);
        vector<int> R = solve(n, D);
        if (!R.empty())
            for (int v: R) {
                for (int i = n-1; i >= 0; --i)
                    putchar('0' + ((v >> i) & 1));
                putchar('\n');
            }
        else
            printf("impossible\n");
    }
}
