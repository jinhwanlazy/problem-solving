#include <bits/stdc++.h> 
using namespace std;

void render(vector<string>& canvas, int order, int i, int j) 
{
	if (order == 1) {
		canvas[i][j] = '*';
		return;
	}
	int step = order / 3;
	for (int di = 0; di < order; di += step) {
		for (int dj = 0; dj < order; dj += step) {
			if (di != step || dj != step) {
				render(canvas, step, i+di, j+dj);
			}
		}
	}
}

int main()
{
	int N;
	cin >> N;
	vector<string> canvas(N, string(N, ' '));

	render(canvas, N, 0, 0);
	for (const auto& row : canvas) {
		cout << row << "\n";
	}

	return 0;
}
