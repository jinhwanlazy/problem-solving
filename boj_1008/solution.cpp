#include <bits/stdc++.h> 
using namespace std;

void solve() 
{
	int a, b;
	cin >> a >> b;
	int last_digit = a % 10;
	int i = last_digit;
	int loop_length = 0;
	do {
		loop_length++;
		i = (last_digit * i) % 10;
	} while (i != last_digit);
	b = (b - 1) % loop_length;
	i = last_digit;
	for (int j = 0; j < b; ++j) {
		i = (last_digit * i) % 10;
	}
	cout << (i > 0 ? i : 10) << "\n";
}

int main()
{
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

