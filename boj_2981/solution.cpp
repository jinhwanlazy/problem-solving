#include <bits/stdc++.h>
using namespace std;

int common_gcd(const vector<int>& xs) {
  return accumulate(xs.begin(), xs.end(), xs[0],
                    [](int a, int b) { return gcd(a, b); });
}

vector<int> get_factors(int x) {
  set<int> factors;
  for (int i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      factors.insert(i);
      factors.insert(x / i);
    }
  }
  return vector<int>(++factors.begin(), factors.end());
}

int main() {
  int N;
  cin >> N;

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }
  sort(xs.begin(), xs.end());

  vector<int> diffs;
  diffs.reserve(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    diffs.push_back(xs[i + 1] - xs[i]);
  }

  int max_factor = common_gcd(diffs);
  vector<int> factors = get_factors(max_factor);
  for (int f : factors) {
    cout << f << " ";
  }
  cout << "\n";
  return 0;
}
