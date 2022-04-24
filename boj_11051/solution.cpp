#include <bits/stdc++.h> 
using namespace std;

constexpr int MOD = 10007;

int bino(int n, int k) 
{
	static vector<vector<int>> memo(1001, vector<int>(1001, -1));
	int& res = memo[n][k];
	if (res != -1) {
		return res;
	}
	if (k <= 0) {
		res = 1;
		return res;
	}
	if (n <= k) {
		res = 1;
		return res;
	}
	res = (bino(n-1, k) + bino(n-1, k-1)) % MOD;
	return res;
}

int main()
{
	int N, K;
	cin >> N >> K;
	cout << bino(N, K) << "\n";
	return 0;
}
