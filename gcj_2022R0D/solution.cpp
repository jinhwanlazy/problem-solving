#include <bits/stdc++.h> 
using namespace std;
using ll = long long;


ll solution() 
{
	size_t N; 
	cin >> N;
	vector<ll> Fs(N+1, 0);
	for (size_t i = 1; i <= N; ++i) {
		cin >> Fs[i];
	}
	vector<ll> Ps(N+1, 0);
	set<int> nonInitiators;
	for (size_t i = 1; i <= N; ++i) {
		int p;
		cin >> p;
		nonInitiators.insert(p);
		Ps[i] = p;
	}
	vector<ll> chainedFun(N+1, -1);
	vector<size_t> prevIdx(N+1);
	for (size_t i = 1; i <= N; ++i) {
		if (nonInitiators.find(i) != nonInitiators.end()) {
			continue;
		}
		//cout << "init - " << i << "\n";
		chainedFun[i] = Fs[i];
		int j = i;
		int k = Ps[i];
		do {
			if (chainedFun[k] != -1 && chainedFun[k] < max(chainedFun[j], Fs[j])) {
				break;
			}
			chainedFun[k] = max(chainedFun[j], Fs[j]);
			prevIdx[k] = j;
			//cout << i << ", " << j << ", " << k << ", " << chainedFun[k] << "\n";
			j = k;
			k = Ps[k];
		} while (j > 0);
	}

	ll res = 0;
	for (size_t i = 1; i <= N; ++i) {
		if (nonInitiators.find(i) != nonInitiators.end()) {
			continue;
		}
		int j = i;
		int k = Ps[i];
		ll tmp = Fs[i];
		do {
			if (j != prevIdx[k]) {
				break;
			}
			tmp = max(tmp, Fs[k]);
			j = k;
			k = Ps[k];
		} while (j > 0);
		//cout << i << " , " << tmp << "\n";
		res += tmp;
	}
	return res;

	//return search(Fs, tree, 0).sum();
}

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cout << "Case #" << t << ": " << solution() << "\n";
	}
	return 0;
}
