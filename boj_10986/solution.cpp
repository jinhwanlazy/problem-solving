#include <bits/stdc++.h> 
using namespace std;

using LL = long long;

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);

	vector<LL> xs(N);
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &xs[i]);
	}

	vector<LL> acc{0};
	for (int i = 0; i < N; ++i) {
		acc.push_back(acc.back() + xs[i]);
	}

	vector<LL> mod_idx_cnt(M, 0);
	for (int i = 0; i <= N; ++i) {
		mod_idx_cnt[acc[i] % M]++;
	}

	LL ans = 0;
	for (LL cnt : mod_idx_cnt) {
		if (cnt >= 2) {
			ans += cnt * (cnt-1) / 2;
		}
	}
	printf("%lld\n", ans);
	
	return 0;
}
