#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

int main() {
	int N;
	scanf("%d", &N);

	while (N--) {
		string s;
		cin >> s;
		cout << s.front() << s.back() << "\n";
	}
	return 0;
}
