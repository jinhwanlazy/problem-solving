#include <bits/stdc++.h> 
using namespace std;

long solve(long y) 
{
	long a = (long)((sqrt(4*y+1) - 1) * 0.5);
	long b = (y - a*(a+1)) / (a+1);
	long c = ((y - a*(a+1)) % (a+1)) != 0; 
	return 2*a + b + c;
}

void solve() 
{
	long x, y;
	cin >> x >> y;
	cout << solve(y-x) << "\n";
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
