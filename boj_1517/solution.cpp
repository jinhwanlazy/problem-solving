#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

template <typename T>
LL merge_(typename vector<T>::iterator lLeft,
           typename vector<T>::iterator lRight,
           typename vector<T>::iterator rLeft,
           typename vector<T>::iterator rRight) {
  vector<T> tmp;
  tmp.reserve(rRight - lLeft);
  auto begin = lLeft;

  LL countInv = 0;
  while (lLeft != lRight || rLeft != rRight) {
    if (lLeft == lRight) {
      tmp.push_back(*rLeft);
      rLeft++;
    } else if (rLeft == rRight || *lLeft <= *rLeft) {
      tmp.push_back(*lLeft);
      lLeft++;
    } else {
      countInv += lRight - lLeft;
      tmp.push_back(*rLeft);
      rLeft++;
    }
  }
  copy(tmp.begin(), tmp.end(), begin);
  return countInv;
}

template <typename T>
LL mergeSort(typename vector<T>::iterator left, typename vector<T>::iterator right) {
  if (left + 1 == right) {
    return 0;
  }
  LL countInv = 0;
  auto mid = left + (right - left) / 2;
  countInv += mergeSort<T>(left, mid);
  countInv += mergeSort<T>(mid, right);
  countInv += merge_<T>(left, mid, mid, right);
  return countInv;
}

int main() {

  int N;
  scanf("%d", &N);

  vector<LL> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &xs[i]);
  }

  LL ans = mergeSort<LL>(xs.begin(), xs.end());
  printf("%lld\n", ans);
  return 0;
}
