#include <bits/stdc++.h>
using namespace std;

int f(const string& s) {
	char last = s.back();
	int res = 0;
	for (char ch : s) {
		if (ch != last) res++;
		last = ch;
	}
	return res;
}

bool test(int N, const string& from, const string& to) {
	assert(from != to);
	int a = f(from), b = f(to);
	if (a > b) return true;
	if (a < b) return false;
	return a != 0 && a != N;
}

int main() {
	int N;
	cin.exceptions(~cin.goodbit);
	string from, to;
	cin >> N >> from >> to;
	cout << (test(N, from, to) ? "yes" : "no") << endl;
}
