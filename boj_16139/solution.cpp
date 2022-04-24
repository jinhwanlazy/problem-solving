#include <bits/stdc++.h> 
using namespace std;

int main()
{
	string S;
	cin >> S;
	
	vector<vector<int>> acc(26, vector<int>(S.size()+1, 0));
	for (int i = 0; i < S.size(); ++i) {
		char c = S[i] - 'a';
		for (char j = 0; j < 26; ++j) {
			if (c == j) {
				acc[j][i+1] = acc[j][i] + 1;
			}
			else {
				acc[j][i+1] = acc[j][i];
			}
		}
	}

	int M;
	scanf("%d", &M);
	for (int i = 0; i < M; ++i) {
		char a;
		int l, r;
		scanf(" %c %d %d", &a, &l, &r);
		//printf("%d %d %d\n", a, l, r);
		a -= 'a';
		printf("%d\n", acc[a][r+1] - acc[a][l]);
	}
	
	return 0;
}
