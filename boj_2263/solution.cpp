#include <bits/stdc++.h> 
using namespace std;

struct IndexPair {
	int in_l;
	int in_r;
	int post_l;
	int post_r;
};

int main()
{
	int N;
	scanf("%d", &N);
	
	vector<int> in_idx(N+1);
	vector<int> in(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &in[i]);
		in_idx[in[i]] = i;
	}

	vector<int> post(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &post[i]);
	}

	vector<IndexPair> s;
	s.push_back({0, N-1, 0, N-1});
	while (!s.empty()) {
		auto [in_l, in_r, post_l, post_r] = s.back();
		s.pop_back();
		
		if (in_l > in_r || post_l > post_r) {
			continue;
		}
		int root = post[post_r];
		printf("%d ", root);

		int i = in_idx[root];
		int l_size = i - in_l - 1;
		s.push_back({i+1, in_r, post_l + l_size + 1, post_r - 1});
		s.push_back({in_l, i-1, post_l, post_l + l_size});
	}
	printf("\n");
	

	return 0;
}
