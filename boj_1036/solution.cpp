#include <bits/stdc++.h>
using namespace std;

template <unsigned N, char const* charset>
class BaseN {
 public:
  BaseN() : data_(0, 0) {}

  BaseN(const string& s) : data_(s.size(), 0) {
    for (size_t i = 0; i < s.size(); ++i) {
      data_[s.size() - i - 1] = BaseN::c2i(s[i]);
    }
  }

  BaseN(size_t digit, unsigned char value) : data_(digit + 1) {
    assert(value < N);
    data_[digit] = value;
  }

  ~BaseN(){};

 public:
  size_t size() const { return data_.size(); }

  BaseN& replace(size_t from, size_t to) {
    for (auto& i : data_) {
      if (i == from)
        i = to;
    }
    return *this;
  }

  BaseN& replace(char from, char to) { return replace(c2i(from), c2i(to)); }

  unsigned operator[](size_t i) { return data_[i]; }

  unsigned operator[](size_t i) const { return data_[i]; }

  BaseN& operator+=(const BaseN& rhs) {
    for (size_t i = 0, end = max(data_.size(), rhs.data_.size()); i < end;
         ++i) {
      if (data_.size() <= i) {
        data_.resize(i + 1, 0);
      }
      data_[i] += rhs.data_[i];
      if (data_[i] >= N && data_.size() < i + 2) {
        data_.resize(i + 2, 0);
      }
      data_[i + 1] += data_[i] / N;
      data_[i] = data_[i] % N;
    }
    removeTrailing0();
    return *this;
  }

  BaseN& operator<<(size_t shift) {
    data_.insert(data_.begin(), 1, 0);
    return *this;
  }

  BaseN& operator>>(size_t shift) {
    if (!data_.empty()) {
      data_.erase(data_.begin());
    }
    return *this;
  }

  friend bool operator<(const BaseN& lhs, const BaseN& rhs) {
    if (lhs.data_.size() != rhs.data_.size()) {
      return lhs.data_.size() < rhs.data_.size();
    }
    if (lhs.size() == 0) {
      return false;
    }
    for (size_t i = lhs.data_.size(); i-- > 0;) {
      if (lhs.data_[i] < rhs.data_[i]) {
        return true;
      }
    }
    return false;
  }

  friend bool operator==(const BaseN& lhs, const BaseN& rhs) {
    if (lhs.data_.size() != rhs.data_.size()) {
      return false;
    }
    for (size_t i = lhs.data_.size(); i-- > 0;) {
      if (lhs.data_[i] != rhs.data_[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator>(const BaseN& lhs, const BaseN& rhs) {
    return rhs < lhs;
  }

  friend ostream& operator<<(ostream& os, const BaseN& rhs) {
    if (rhs.size() == 0) {
      os << charset[0];
      return os;
    }
    for (auto it = rhs.data_.rbegin(); it != rhs.data_.rend(); ++it) {
      os << i2c(*it);
    }
    return os;
  }

 public:
  static size_t c2i(char c) {
    for (size_t i = 0; i < N; ++i) {
      if (c == charset[i]) {
        return i;
      }
    }
    return -1;
  }

  static char i2c(unsigned char i) { return charset[i]; }

 private:
  void removeTrailing0() {
    while (!data_.empty() && data_.back() == 0) {
      data_.pop_back();
    }
  }

 private:
  vector<unsigned char> data_;
};

char BASE36CHARSET[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
typedef BaseN<36, BASE36CHARSET> Base36;

signed main() {
  int N, K;
  cin >> N;

  vector<Base36> words;
  for (int i = 0; i < N; ++i) {
    string word;
    cin >> word;
    words.emplace_back(word);
  }
  cin >> K;

  vector<Base36> weights(36);
  for (const auto& word : words) {
    for (size_t i = 0; i < word.size(); ++i) {
      auto x = word[i];
      Base36 w(i, 35 - x);
      weights[x] += w;
    }
  }

  vector<size_t> idxs(36);
  for (int i = 0; i < 36; ++i) {
    idxs[i] = i;
  }
  std::sort(idxs.begin(), idxs.end(),
            [&](int lhs, int rhs) { return weights[lhs] > weights[rhs]; });

  for (int i = 0; i < K; ++i) {
    for (auto& word : words) {
      word.replace(idxs[i], 35);
      cout << word << "\n";
    }
  }

  Base36 ans;
  for (const auto& word : words) {
    ans += word;
  }
  cout << ans;
  return 0;
}
