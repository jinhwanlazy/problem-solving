#include <bits/stdc++.h> 
using namespace std;

int solution(const vector<int>& xs) 
{
	int K = xs.size();
	vector<vector<int>> sum(K, vector<int>(K, 0));

	for (int i = 0; i < K; ++i) {
		for (int j = i; j < K; ++j) {
			if (i == j) {
				sum[i][j] = xs[i];
			}
			else {
				sum[i][j] = sum[i][j-1] + xs[j];
			}
		}
	}

	// dp[l][r] : min cost of range [l, r], both inclusive.
	vector<vector<int>> dp(K, vector<int>(K, numeric_limits<int>::max()));
	for (int i = 0; i <= K; ++i) {
		for (int l = 0; l + i < K; ++l) {
			int r = l+i;
			if (i == 0) {
				dp[l][r] = 0;
				continue;
			}
			else if (i == 1) {
				dp[l][r] = xs[l] + xs[r];
				continue;
			}
			for (int m = l; m < r; ++m) {
				int cost = sum[l][r];
				dp[l][r] = min(dp[l][r], dp[l][m] + dp[m+1][r] + cost);
			}
		}
	}

	return dp[0][K-1];
}

int main()
{
	int N;
	cin >> N;
	while (N--) {
		int K;
		cin >> K;
		vector<int> xs(K);
		for (int i = 0; i < K; ++i) {
			cin >> xs[i];
		}
		cout << solution(xs) << "\n";
	}
	return 0;
}
