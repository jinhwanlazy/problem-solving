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

void solution() 
{
	int F;
	cin >> F;

	UnionFindSet uf(200001);
	unordered_map<string, int> dict;
	while (F--) {
		string A, B;
		cin >> A >> B;
		auto a_it = dict.find(A);
		auto b_it = dict.find(B);
		int i, j;
		if (a_it == dict.end()) {
			i = dict.size();
			dict.insert({A, dict.size()});
		}
		else {
			i = a_it->second;
		}
		if (dict.count(B) == 0) {
			j = dict.size();
			dict.insert({B, dict.size()});
		}
		else {
			j = b_it->second;
		}
		//uf.resize(dict.size());
		int ans = uf.merge(i, j);
		cout << ans << '\n';
	}
	//for (const auto& [name, idx] : dict) {
		//cout << name << ": " << idx << "\n";
	//}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	
	while (T--) {
		solution();
	}
	
	return 0;
}
