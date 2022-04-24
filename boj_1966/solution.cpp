#include <bits/stdc++.h> 
using namespace std;

int solution(const vector<int>& docs, int M) 
{
	deque<pair<int, int>> Q;
	for (int i = 0; i < docs.size(); ++i) {
		Q.push_back({i, docs[i]});
	}

	int count = 0;
	while (!Q.empty()) {
		int idx = Q.front().first;
		int priority = Q.front().second;
		Q.pop_front();
		bool is_max_priority = true;
		for (int i = 0; i < Q.size(); ++i) {
			if (Q[i].second > priority) {
				is_max_priority = false;
				break;
			}
		}
		if (is_max_priority) {
			count++;
			if (idx == M) {
				break;
			}
		}
		else {
			Q.push_back({idx, priority});
		}
		//for (int i = 0; i < Q.size(); ++i) {
			//cout << "(" << Q[i].first << ", " << Q[i].second << "), ";
		//}
		//cout << "\n";
	}
	return count;
}

int main()
{
	int T;
	cin >> T;

	while (T--)  {
		int N, M;
		cin >> N >> M;
		vector<int> docs(N);
		for (int i = 0; i < N; ++i) {
			cin >> docs[i];
		}
		cout << solution(docs, M) << "\n";
	}

	return 0;
}
