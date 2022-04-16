#include <bits/stdc++.h> 
using namespace std;

int solution(int N)
{
	if (N == 1) {
		return 0;
	}

	static vector<int> memo(N+1, -1);
	int& res = memo[N];
	if (res != -1) {
		return res;
	}
	res = 1 + solution(N-1);
	if (N % 3 == 0) {
		res = min(res, 1 + solution(N / 3));
	}
	if (N % 2 == 0) {
		res = min(res, 1 + solution(N / 2));
	}
	return res;
}

int main()
{
	int N;
	cin >> N;
	cout << solution(N) << "\n";
	return 0;
}
