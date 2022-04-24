#include <bits/stdc++.h> 
using namespace std;

int main()
{
	vector<int> v;
	v.push_back(numeric_limits<int>::min());

	int N;
	scanf("%d", &N);
	
	while (N--) {
		int i;
		scanf("%d", &i);
		if (v.back() < i) {
			v.push_back(i);
		}
		else {
			auto it = lower_bound(v.begin(), v.end(), i);
			*it = i;
		}
	}
	printf("%ld", v.size()-1);
	return 0;
}
