#include <bits/stdc++.h> 
using namespace std;


int knapsack(int N, int K, const vector<int>& W, const vector<int>& V) 
{
	/*
	 * dp[i][j] := 1~i번째 물건으로 크기 j인 배낭을 채웠을 때의 최대 가치
	 */
	vector<vector<int>> dp(N+1, vector<int>(K+1, 0));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= K; ++j) {
			int w = W[i-1];
			int v = V[i-1];
			if (w > j) {
				dp[i][j] = dp[i-1][j];
			}
			else {
				dp[i][j] = max(
					dp[i-1][j-w] + v,
					dp[i-1][j]
				);
			}
		}
	}
	return dp.back().back();
}

int main()
{
	int N, K;
	scanf("%d %d", &N, &K);
	vector<int> W(N), V(N);

	for (int i = 0; i < N; ++i) {
		scanf("%d %d", &W[i], &V[i]);
	}

	cout << knapsack(N, K, W, V) << "\n";
	return 0;
}
