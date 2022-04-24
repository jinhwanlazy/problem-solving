#include <bits/stdc++.h> 
using namespace std;

using LL = long long;

int main()
{
	int N;
	cin >> N;

	vector<LL> dists(N, 0);
	vector<LL> costs(N);
	for (int i = 0; i < N-1; ++i) {
		scanf("%lld", &dists[i]);
	}
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &costs[i]);
	}

	LL total_cost = 0;
	for (int i = 0; i < N;) {
		int j = i;
		while (costs[i] <= costs[j] && j < N) {
			total_cost += dists[j] * costs[i];
			j++;
		}
		i = j;
	}
	cout << total_cost << "\n";

	return 0;
}
