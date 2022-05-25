#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
	cin.tie(NULL);

  int N, M;
  cin >> N >> M;
  
  unordered_map<string, string> dict;
  for (int i = 0; i < N; ++i) {
    string k, v;
    cin >> k >> v;
    dict[k] = v;
  }
  for (int i = 0; i < M; ++i) {
    string k;
    cin >> k;
    cout << dict[k] << "\n";
  }

  return 0;
}
