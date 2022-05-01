#include <bits/stdc++.h> 
using namespace std;

struct UnionFindSet {
	UnionFindSet(int size) : root_(size), rank_(size, 0), size_(size, 1) {
		for (int i = 0; i < size; ++i) {
			root_[i] = i;
		}
	}

	int find(int i) {
		if (root_[i] == i) {
			return i;
		}
		int root = find(root_[i]);
		root_[i] = root;
		return root;
	}

	int merge(int i, int j) {
		int i_root = find(i);
		int j_root = find(j);
		if (i_root == j_root) {
			return size_[i_root];
		}
		if (rank_[i_root] < rank_[j_root]) {
			root_[i_root] = j_root;
			size_[j_root] += size_[i_root];
			size_[i_root] = 0;
			return size_[j_root];
		}
		root_[j_root] = i_root;
		size_[i_root] += size_[j_root];
		size_[j_root] = 0;
		if (rank_[i_root] == rank_[j_root]) {
			rank_[i_root]++;
		}
		return size_[i_root];
	}

	bool resize(size_t size) {
		size_t size_before = root_.size();

		if (size_before >= size) {
			return false;
		}
		root_.resize(size);
		rank_.resize(size, 0);
		size_.resize(size, 1);
		for (int i = size_before; i < size; ++i) {
			root_[i] = i;
		}
		return true;
	}

	size_t size() const {
		return root_.size();
	}

	vector<int> root_;
	vector<int> rank_;
	vector<int> size_;
};

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	
	UnionFindSet ufs(N);
	int end = 0;
	
	for (int i = 0; i < M; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		
		if (ufs.find(u) == ufs.find(v)) {
			if (end == 0) {
				end = i+1;
			}
		}
		ufs.merge(u, v);
	}
	printf("%d\n", end);
	return 0;
}
