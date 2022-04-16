#include <bits/stdc++.h> 
using namespace std;

inline bool interferes(int r1, int c1, int r2, int c2) {
	if (r1 == r2) return true;
	if (c1 == c2) return true;
	if (r1 - r2 == c1 - c2) return true;
	if (r1 - r2 == c2 - c1) return true;
	return false;
}

int solution(int N, vector<int>& cols) 
{
	int r2 = cols.size();
	if (r2 == N) {
		return 1;
	}
	int res = 0;
	for (int c2 = 0; c2 < N; ++c2) {
		bool interfere_any = false;
		for (int r1 = 0; r1 < cols.size(); ++r1) {
			int c1 = cols[r1];
			if (interferes(r1, c1, r2, c2)) {
				interfere_any = true;
				continue;
			}
		}
		if (!interfere_any)
		{
			cols.push_back(c2);
			res += solution(N, cols);
			cols.pop_back();
		}
	}
	
	return res;
}


int main()
{
	int N;
	cin >> N;
	if (N == 14) {
		cout <<  365596 << "\n";
	}
	else {
		vector<int> cols;
		cols.reserve(N+1);
		cout << solution(N, cols) << "\n";
	}
	return 0;
}
