#include <bits/stdc++.h> 
using namespace std;

int LCS(const string& A, const string& B) 
{
	/*
	 * dp[i][j] := LCS(A[:i], B[:j])
	 */
	vector<vector<int>> dp(A.size()+1, vector<int>(B.size()+1, 0));
	for (int i = 1; i <= A.size(); ++i) {
		for (int j = 1; j <= B.size(); ++j) {
			if (A[i-1] == B[j-1]) {
				dp[i][j] = dp[i-1][j-1] + 1;
			}
			else {
				dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
			}
		}
	}
	return dp.back().back();
}

int main()
{
	string A, B;
	cin >> A >> B;
	cout << LCS(A, B) << "\n";
	return 0;
}
