#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<int> xs(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &xs[i]);
	}

	vector<int> nge(N, -1);
	vector<int> s;
	
	for (int i = N-1; i >= 0; --i) {
		while (!s.empty() && s.back() <= xs[i]) {
			s.pop_back();
		}
		if (!s.empty()) {
			nge[i] = s.back();
		}
		s.push_back(xs[i]);

	}
	for (int i = 0; i < N; ++i) {
		printf("%d ", nge[i]);
	}
	printf("\n");

	return 0;
}
