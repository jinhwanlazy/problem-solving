#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int N;
	scanf("%d", &N);

	vector<int> xs(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &xs[i]);
	}

	vector<vector<bool>> dp(N, vector<bool>(N, false));
	for (int i = 0; i < N; ++i) {
		for (int l = 0; l + i < N ; ++l) {
			int r = l+i;
			if (i == 0) {
				dp[l][r] = true;
			}
			else if (i == 1) {
				dp[l][r] = (xs[l] == xs[r]);
			}
			else {
				dp[l][r] = dp[l+1][r-1] & (xs[l] == xs[r]);
			}
		}
	}
	
	int M;
	scanf("%d", &M);
	for (int i = 0; i < M; ++i) {
		int l, r;
		scanf("%d %d", &l, &r);
		cout << int(dp[l-1][r-1]) << "\n";
	}
	return 0;
}
