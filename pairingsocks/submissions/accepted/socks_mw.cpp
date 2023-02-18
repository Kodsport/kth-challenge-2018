#include <iostream>
#include <stack>

using namespace std;

int main() {
	int N;
	cin >> N;
	stack<int> original, auxiliary;
	for (int i = 0; i < 2*N; i++) {
		int a;
		cin >> a;
		original.push(a);
	}
	int moves = 0;
	while (original.size() > 0) {
		auxiliary.push(original.top());
		original.pop();
		moves++;
		while(original.size() > 0 && auxiliary.size() > 0 && original.top() == auxiliary.top()) {
			original.pop();
			auxiliary.pop();
			moves++;
		}
	}
	if (auxiliary.size() > 0)
		cout << "impossible" << endl;
	else
		cout << moves << endl;
}
