#include <bits/stdc++.h> 
using namespace std;

constexpr int MOD = 1000000007;

int bino(int n, int k) 
{
	static map<pair<int, int>, int> memo;
	auto it = memo.find({n, k});
	if (it != memo.end()) {
		return it->second;
	}
	int& res = memo[{n, k}];
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
