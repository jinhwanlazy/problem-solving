#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<int> xs(N);
	for (int i = 0; i < N; ++i) {
		cin >> xs[i];
	}

	vector<int> dp(N);
	dp[0] = xs[0];
	for (int i = 1; i < N; ++i) {
		dp[i] = max(xs[i], dp[i-1] + xs[i]);
	}

	cout << *max_element(dp.begin(), dp.end()) << "\n";

	return 0;
}
