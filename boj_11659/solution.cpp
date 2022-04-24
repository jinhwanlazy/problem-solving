#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<int> xs(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &xs[i]);
	}
	
	vector<int> acc(N+1, 0);
	for (int i = 0; i < N; ++i) {
		acc[i+1] = acc[i] + xs[i];
	}

	for (int i = 0; i < M; ++i) {
		int l, r;
		scanf("%d %d", &l, &r);

		printf("%d\n", acc[r] - acc[l-1]);
	}
	return 0;
}
