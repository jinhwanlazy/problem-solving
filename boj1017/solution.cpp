#include <bits/stdc++.h> 
using namespace std;

class BipartiteMatching
{
public:
	BipartiteMatching(uint64_t nSrcNodes, uint64_t nDstNodes) 
		: edges_(nSrcNodes, std::vector<bool>(nDstNodes, 0))
		, matches_(nDstNodes, -1)
		, visited_(nSrcNodes, false)
	{
	} 

	void addEdge(uint64_t src, uint64_t dst) {
		edges_[src][dst] = 1;
	}

	size_t solve() {
		size_t res = 0;
		for (size_t i = 0; i < edges_.size(); ++i) {
			std::fill(visited_.begin(), visited_.end(), false);
			res += dfs(i);
		}
		return res;
	}

	std::vector<std::pair<uint64_t, uint64_t>> matches() const {
		std::vector<std::pair<uint64_t, uint64_t>> res;
		for (size_t dst = 0; dst < matches_.size(); ++dst) {
			const auto& src = matches_[dst];
			if (src != -1) {
				res.push_back({src, dst});
			}
		}
		return res;
	}

private:
	bool dfs(uint64_t src) {
		if (visited_[src]) {
			return false;
		}
		visited_[src] = true;
		for (size_t dst = 0; dst < edges_[src].size(); ++dst) {
			if (!edges_[src][dst]) {
				continue;
			}
			if (matches_[dst] >= edges_.size() || dfs(matches_[dst])) {
				matches_[dst] = src;
				return true;
			}
		}
		return false;
	}

private:
	std::vector<std::vector<bool>> edges_;
	std::vector<uint64_t> matches_;
	std::vector<bool> visited_;
};

bool isPrime(int number){
    if(number < 2) return false;
    if(number == 2) return true;
    if(number % 2 == 0) return false;
    for(int i=3; (i*i)<=number; i+=2){
        if(number % i == 0 ) return false;
    }
    return true;
}

bool test(const vector<int>& xs, const int idx) {
	vector<int> odds, evens;
	for (int i = 1; i < xs.size(); ++i) {
		if (i == idx) continue;
		if (xs[i] % 2 == 0) 
			evens.push_back(xs[i]);
		else 
			odds.push_back(xs[i]);
	}
	if (evens.size() != odds.size()) {
		return false;
	}
	
	BipartiteMatching bm(odds.size(), evens.size());
	for (int i = 0; i < odds.size(); ++i) {
		for (int j = 0; j < evens.size(); ++j) {
			if (isPrime(odds[i] + evens[j])) {
				bm.addEdge(i, j);
			}
		}
	}
	return bm.solve() == odds.size();
}

int main()
{
	int N;
	cin >> N;
	
	vector<int> xs(N);
	for (int i = 0; i < N; ++i) {
		cin >> xs[i];
	}

	vector<int> ans;
	for (int i = 1; i < N; ++i) {
		if (isPrime(xs[0] + xs[i]) && test(xs, i)) {
			ans.push_back(xs[i]);
		}
	}
	if (ans.empty()) {
		cout << "-1\n";
	}
	else {
		sort(ans.begin(), ans.end());
		for (int i : ans) {
			cout << i << " ";
		}
		cout << "\n";
	}
	return 0;
}
