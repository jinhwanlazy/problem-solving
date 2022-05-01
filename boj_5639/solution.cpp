#include <bits/stdc++.h> 
using namespace std;

void solve(const vector<int>& pre, int l, int r) {
	if (l > r) {
		return;
	}
	int root = pre[l];
	
	auto it = upper_bound(pre.begin() + l, pre.begin() + r + 1, root);
	int new_r = it - pre.begin();
	solve(pre, l+1, new_r-1);
	solve(pre, new_r, r);

	cout << root << "\n";
}

int main()
{
	vector<int> pre;
	int i = 0;
	while (cin >> i) {
		pre.push_back(i);
	}

	solve(pre, 0, pre.size()-1);
	return 0;
}
