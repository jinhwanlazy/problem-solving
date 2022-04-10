#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

int main()
{
	ll N, L;
	cin >> N >> L;

	for (ll i = L; i <= 100; ++i) {
		ll l = (N / i) - ((i - 1) / 2);
		ll r = (N / i) + i / 2;
		if (l < 0) {
			continue;
		}
		ll sum = r * (r+1) / 2 - l * (l - 1) / 2;
		if (N != sum) {
			continue;
		}
		for (ll i = l; i <= r; ++i) {
			cout << i << " ";
		}
		return 0;
	}
	cout << "-1";
	return 0;
}
