#include <bits/stdc++.h> 
using namespace std;

using LL = long long;

vector<LL> allPossibleWeights(const vector<LL>& W, LL limit) {
	vector<LL> res;
	res.reserve(1 << W.size());
	for (LL w : W) {
		if (res.empty()) {
			res.push_back(0);
			if (w <= limit) {
				res.push_back(w);
			}
			
		}
		else {
			for (LL i : res) {
				if (i + w <= limit) {
					res.push_back(i + w);
				}
			}
		}
	}
	sort(res.begin(), res.end());
	return res;
}

int main()
{
	int N;
	LL C;
	scanf("%d %lld", &N, &C);

	vector<LL> W(N);
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &W[i]);
	}

	if (N == 1) {
		if (W[0] > C) {
			printf("1\n");
		}
		else {
			printf("2\n");
		}
		return 0;
	}

	int m = N / 2;
	vector<LL> l_half(W.begin(), W.begin() + m);
	vector<LL> r_half(W.begin() + m, W.end());

	auto l_sums = allPossibleWeights(l_half, C);
	auto r_sums = allPossibleWeights(r_half, C);

	int l = 0;
	int r = r_sums.size()-1;
	
	int count = 0;
	while (l < l_sums.size()) {
		while (l_sums[l] + r_sums[r] < C && r < r_sums.size()-1) {
			r++;
		}
		while (l_sums[l] + r_sums[r] > C && r > 0) {
			r--;
		}
		count += r + 1;
		l++;
	}

	printf("%d\n", count);
	return 0;
}
