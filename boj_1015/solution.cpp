#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int N;
	cin >> N;
	vector<pair<int, int>> A;
	vector<int> P(N);
	
	for (int i = 0; i < N; ++i) {
		int a;
		cin >> a;
		A.push_back({a, i});
	}
	std::sort(A.begin(), A.end());
	for (int i = 0; i < N; ++i) {
		P[A[i].second] = i;
	}
	for (int i = 0; i < N; ++i) {
		cout << P[i] << " ";
	}
	return 0;
}
