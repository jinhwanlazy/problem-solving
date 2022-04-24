#include <bits/stdc++.h> 
using namespace std;

using LL = long long;

int main()
{
	LL N, M;
	cin >> N >> M;
	vector<LL> H(N);
	for (int i = 0; i < N; ++i) {
		cin >> H[i];
	}

	int r = *max_element(H.begin(), H.end());
	int l = 0;
	while (l+1 < r) {
		int m = (r + l) / 2;
		LL trees = accumulate(H.begin(), H.end(), 0LL, [m](LL a, LL b) {
				return a + max(0LL, b - m);
			});
		
		if (M <= trees) {
			l = m;
		}
		else {
			r = m;
		}
	}
	cout << l << "\n";
	return 0;
}
