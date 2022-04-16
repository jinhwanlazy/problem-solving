#include <bits/stdc++.h> 
using namespace std;

class Sieve 
{
public:
	Sieve(size_t max_size) : sieve_(max_size, true) {
		sieve_[0] = false;
		sieve_[1] = false;
		for (size_t i = 2; i < max_size; ++i) {
			if (!sieve_[i]) {
				continue;
			}
			for (size_t j = i * 2; j < max_size; j += i) {
				sieve_[j] = false;
			}
		}
	}
	
	bool isPrime(size_t i) const {
		return sieve_[i];
	}
	
private:
	vector<bool> sieve_;
};


#include <bits/stdc++.h> 
using namespace std;

int solution(const Sieve& sieve) 
{
	int n;
	cin >> n;
	int ans = 0;
	for (size_t i = 2; i <= n / 2; ++i) {
		if (sieve.isPrime(i) && sieve.isPrime(n - i)) {
			ans = i;
		}
	}
	cout << ans << " " << n - ans << "\n";
	return 0;
}

int main()
{
	int N;
	cin >> N;
	Sieve sieve(20000);
	while (N--) {
		solution(sieve);
	}
	return 0;
}
