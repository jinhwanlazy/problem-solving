#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<int> glasses(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> glasses[i];
	}
	/* 
	 * dp[i][j] := j번째 계단에서 점수의 최대값. i는 이전 step에서 1계단을
	 * 올랐음을 나타내는 flag.
	 */
	vector<vector<int>> dp(2, vector<int>(N, -1));
	dp[0][0] = glasses[0];
	int res = dp[0][0];
	if (N > 1) {
		dp[0][1] = glasses[1];
		dp[1][1] = glasses[0] + glasses[1];
		res = max(res, dp[0][1]);
		res = max(res, dp[1][1]);
	}
	for (int j = 2; j < N; ++j) {
		dp[0][j] = max(dp[0][j-2], dp[1][j-2]);
		//dp[0][j] = max(dp[0][j], dp[0][j-3]);
		dp[0][j] = max(dp[0][j], dp[1][j-3]);
		dp[0][j] += glasses[j];
		dp[1][j] = dp[0][j-1] + glasses[j];
		res = max(res, dp[0][j]);
		res = max(res, dp[1][j]);
	}
	cout << res << "\n";
	return 0;
}
