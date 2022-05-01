#include <bits/stdc++.h> 
using namespace std;

struct UnionFindSet {
	UnionFindSet(int size) : data_(size), rank_(size, 0) {
		for (int i = 0; i < size; ++i) {
			data_[i] = i;
		}
	}

	int find(int i) {
		if (data_[i] == i) {
			return i;
		}
		int root = find(data_[i]);
		data_[i] = root;
		return root;
	}

	void merge(int i, int j) {
		int i_root = find(i);
		int j_root = find(j);
		if (i_root == j_root) {
			return;
		}
		if (rank_[i_root] == rank_[j_root]) {
			data_[i_root] = j_root;
			rank_[i_root]++;
		}
		else if (rank_[i_root] < rank_[j_root]) {
			data_[i_root] = j_root;
		}
		else {
			data_[j_root] = i_root;
		}
	}

	vector<int> data_;
	vector<int> rank_;
};


int main()
{
	int N, M;
	scanf("%d %d", &N, &M);

	UnionFindSet uf(N);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int c;
			scanf("%d", &c);
			if (c) {
				uf.merge(i, j);
			}
		}
	}

	bool ans = true;
	int root = -1;
	for (int i = 0; i < M; ++i) {
		int x;
		scanf("%d", &x);
		int r = uf.find(x-1);
		if (root == -1) {
			root = r;
		}
		else if (root != r) {
			ans = false;
			break;
		}
	}

	cout << (ans ? "YES" : "NO") << "\n";
	return 0;
}
