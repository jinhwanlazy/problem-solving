#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  ll K, N;
  cin >> K >> N;
  vector<ll> cables(K);
  ll maxCable = 0;
  for (ll i = 0; i < K; ++i) {
    cin >> cables[i];
    maxCable = max(maxCable, cables[i]);
  }

  ll l = 1;
  ll r = maxCable;
  while (l <= r) {
    ll m = (r + l) / 2;
    ll nCables = 0;
    for (ll cable : cables) {
      nCables += cable / m;
    }
    if (nCables < N)
      r = m - 1;
    else
      l = m + 1;
  }
  cout << r << "\n";
}
