#include <bits/stdc++.h> 
using namespace std;

int main()
{
	uint64_t A, B;
	cin >> A >> B;

	vector<int> sieve(B-A+1, 1);

	uint64_t rng = sqrt(double(B));
	for (uint64_t i = 2; i <= rng; ++i) {
		uint64_t sq = i * i;
		for (uint64_t j = A / sq, end = B / sq; j <= end; ++j) {
			uint64_t idx = j*sq - A;
			if (idx < sieve.size()) {
				sieve[idx] = 0;
			}
		}
	}
	
	int count = 0;
	for (int i : sieve) {
		count += i;
	}
	cout << count << "\n";
	
	return 0;
}
