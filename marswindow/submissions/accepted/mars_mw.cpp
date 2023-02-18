#include <iostream>

using namespace std;

int main() {
	int y;
	cin >> y;
	int launchYear = 2018;
	int launchMonth = 3;
	while (launchYear < y) {
		launchMonth += 26;
		while (launchMonth >= 12) {
			launchYear++;
			launchMonth -= 12;
		}
	}
	if (launchYear == y)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}
