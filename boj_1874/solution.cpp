#include <bits/stdc++.h> 
using namespace std;


int main()
{
	int N;
	cin >> N;

	vector<int> xs(N);
	for (int i = 0; i < N; ++i) {
		cin >> xs[i];
	}

	vector<int> s;
	int j = 0;
	vector<char> res;
	
	for (int i = 1; i <= N && j < N; ++i) {
		s.push_back(i);
		res.push_back('+');
		//cout << "push << " << i << "\n";
		//for (int k = 0; k < s.size(); ++k) {
			//cout << s[k] << " ";
		//}
		//cout << "\n";
		
		while (!s.empty() && xs[j] == s.back()) {
			s.pop_back();
			res.push_back('-');
			j++;
			//cout << "pop\n";
			//for (int k = 0; k < s.size(); ++k) {
				//cout << s[k] << " ";
			//}
			//cout << "\n";
		}
	}
	if (j != N) {
		cout << "NO";
	}
	else {
		for (int i = 0; i < res.size(); ++i) {
			cout << res[i] << "\n";
		}
	}
	return 0;
}
