/*
 * dp[0] = 0
 * dp[1] = 1
 * dp[2] = 1
 * dp[3] = 1
 * dp[4] = 2
 * dp[5] = 2 = dp[4] + dp[0]
 * dp[6] = 3 = dp[5] + dp[1]
 * dp[7] = 4 = dp[6] + dp[2]
 * dp[8] = 5 = dp[7] + dp[3]
 * dp[9] = 7 = dp[8] + dp[4]
 * dp[10] = 9 = dp[9] + dp[5]
 * dp[11] = 12 = dp[10] + dp[6]
 * dp[12] = 16 = dp[11] + dp[7]
 */

#include <bits/stdc++.h> 
using namespace std;

int main()
{
	vector<long long> dp(101);
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 1;
	dp[3] = 1;
	dp[4] = 2;
	for (int i = 5; i <= 100; ++i) {
		dp[i] = dp[i-1] + dp[i-5];
	}

	int N;
	cin >> N;

	while (N--) {
		int j;
		cin >> j;
		cout << dp[j] << "\n";
	}
	return 0;
}
