#include <iostream>
#include <map>

using namespace std;

int main() {
    int N;
    cin >> N;
    map<int, int> cnt[2];
    for (int i = 0; i < 2*N; i++) {
        int a;
        cin >> a;
        cnt[i%2][a]++;
    }
    for (auto it : cnt[0]) {
        if (cnt[1][it.first] != it.second) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << 2*N << endl;
}
