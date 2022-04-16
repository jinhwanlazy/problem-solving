#include <bits/stdc++.h> 
using namespace std;

void solution(const vector<int>& xs, vector<int>& ops, int step, int res, int& max_res, int& min_res)
{
	if (step == xs.size()) {
		max_res = max(max_res, res);
		min_res = min(min_res, res);
		return;
	}
	for (size_t i = 0; i < ops.size(); ++i) {
		if (ops[i] > 0) {
			ops[i]--;
			int nxt_res = res;
			switch (i) {
			case 0: nxt_res += xs[step]; break;
			case 1: nxt_res -= xs[step]; break;
			case 2: nxt_res *= xs[step]; break;
			case 3: nxt_res /= xs[step]; break;
			}
			solution(xs, ops, step+1, nxt_res, max_res, min_res);
			ops[i]++;
		}
	}
}

int main()
{
	int N;
	cin >> N;

	vector<int> xs(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &xs[i]);
	}

	vector<int> opCount(4, 0);
	cin >> opCount[0] >> opCount[1] >> opCount[2] >> opCount[3];

	int min_res = 2000000000;
	int max_res = -2000000000;
	solution(xs, opCount, 1, xs[0], max_res, min_res);

	cout << max_res << "\n" << min_res << "\n";
	
	return 0;
}
