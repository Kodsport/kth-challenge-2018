#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 = false, 1 = true

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	int add_var() {
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void either(int f, int j) {
		f = (f >= 0 ? 2*f : -1-2*f);
		j = (j >= 0 ? 2*j : -1-2*j);
		gr[f^1].push_back(j);
		gr[j^1].push_back(f);
	}

	void at_most_one(const vi& li) {
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		rep(i,2,sz(li)) {
			int next = add_var();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}

	vi val, comp, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		trav(e, gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		++time;
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = time;
			if (values[x>>1] == -1)
				values[x>>1] = !(x&1);
		} while (x != i);
		return val[i] = low;
	}

	bool solve() {
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		rep(i,0,2*N) if (!comp[i]) dfs(i);
		rep(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N;
	cin >> N;
	TwoSat ts(2*(N-1));
	vector<vi> left(N), right(N);
	rep(i,0,2*(N-1)) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		assert(a < b);
		right[a].push_back(i);
		left[b].push_back(~i);
	}
	rep(i,0,N-1) {
		ts.at_most_one(right[i]);
		ts.at_most_one(left[i+1]);
	}
	bool r = ts.solve();
	if (!r) {
		cout << "impossible" << endl;
	} else {
		rep(i,0,2*(N-1))
			cout.put(ts.values[i] ? 'R' : 'L');
		cout << endl;
	}
}
