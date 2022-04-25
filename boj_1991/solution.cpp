#include <bits/stdc++.h> 
using namespace std;

void preorderTraversal(const vector<int>& left, const vector<int>& right, int i) {
	printf("%c", i + 'A');
	if (left[i] != -1) preorderTraversal(left, right, left[i]);
	if (right[i] != -1) preorderTraversal(left, right, right[i]);
}

void inorderTraversal(const vector<int>& left, const vector<int>& right, int i) {
	if (left[i] != -1) inorderTraversal(left, right, left[i]);
	printf("%c", i + 'A');
	if (right[i] != -1) inorderTraversal(left, right, right[i]);
}

void postorderTraversal(const vector<int>& left, const vector<int>& right, int i) {
	if (left[i] != -1) postorderTraversal(left, right, left[i]);
	if (right[i] != -1) postorderTraversal(left, right, right[i]);
	printf("%c", i + 'A');
}

int main()
{
	int N;
	scanf("%d", &N);
	
	vector<int> left(N, -1);
	vector<int> right(N, -1);

	for (int i = 0; i < N; ++i) {
		char root, L, R;
		scanf(" %c %c %c", &root, &L, &R);
		if (L != '.') left[root-'A'] = L-'A';
		if (R != '.') right[root-'A'] = R-'A';
	}

	preorderTraversal(left, right, 0);
	printf("\n");

	inorderTraversal(left, right, 0);
	printf("\n");

	postorderTraversal(left, right, 0);
	printf("\n");

	return 0;
}
