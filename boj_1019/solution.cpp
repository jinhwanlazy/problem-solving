#include <bits/stdc++.h>
using namespace std;

struct DigitCounter {
  DigitCounter() {}

  DigitCounter(int digit, int count) { data_[digit] = count; }

  DigitCounter(int n) {
    while (n > 0) {
      data_[n % 10]++;
      n /= 10;
    }
  }

  DigitCounter operator+=(const DigitCounter& rhs) {
    for (int i = 0; i < 10; ++i) {
      this->data_[i] += rhs.data_[i];
    }
    return *this;
  }

  DigitCounter operator+(const DigitCounter& rhs) {
    DigitCounter res;
    for (int i = 0; i < 10; ++i) {
      res.data_[i] = data_[i] + rhs.data_[i];
    }
    return res;
  }

  DigitCounter operator*(int n) {
    DigitCounter res;
    for (int i = 0; i < 10; ++i) {
      res.data_[i] = data_[i] * n;
    }
    return res;
  }

  array<int, 10> data_ = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

ostream& operator<<(ostream& os, const DigitCounter& counter) {
  for (int i = 0; i < 10; ++i) {
    os << counter.data_[i] << " ";
  }
  os << "\n";
  return os;
}

DigitCounter solution(int l, int r) {
  if (l == r) {
    return DigitCounter(l);
  }
  if (l % 10 != 0) {
    return DigitCounter(l) + solution(l + 1, r);
  }
  if (r % 10 != 9) {
    return DigitCounter(r) + solution(l, r - 1);
  }
  DigitCounter counter;
  for (int i = 0; i < 10; ++i) {
    counter += DigitCounter(i, (r / 10) - (l / 10) + 1);
  }
  counter += solution(l / 10, r / 10) * 10;
  return counter;
}

int main() {
  int N;
  cin >> N;
  cout << solution(1, N);
  return 0;
}
