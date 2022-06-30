#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;


int main() {
	string s;
	getline(cin, s);
	s.push_back(' ');
	double x=0, y=0;
	int t=0;
	char d=' ';
	for (char c : s) {
		if ('0' <= c && c <= '9') {
			t = t * 10 + (c - '0');
		}
		else {
			if (d == 'n') y += t;
			if (d == 's') y -= t;
			if (d == 'e') x += t;
			if (d == 'w') x -= t;
			d = c;
			t = 0;
		}
	}

	double ans = sqrt(x*x + y*y);
	printf("%.2lf\n", ans);

	return 0;
}
