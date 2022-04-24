#include <bits/stdc++.h> 
using namespace std;

int main()
{
	priority_queue<int> left;
	priority_queue<int> right;

	int N;
	scanf("%d", &N);
	while (N--) {
		int i;
		scanf("%d", &i);
		left.push(i);
		while (left.size() > right.size() + 1) {
			right.push(-left.top());
			left.pop();
		}
		if (left.size() > 0 && right.size() > 0) {
			while (left.top() > -right.top()) {
				int ltop = left.top();
				int rtop = -right.top();
				left.pop();
				right.pop();
				left.push(rtop);
				right.push(-ltop);
			}
		}
		//if (left.size() > 0 && right.size() > 0) 
		//cout << left.size() << ", " << right.size() << ", " << left.top() << ", " << right.top() << "\n";
		printf("%d\n", left.top());
	}
	return 0;
}
