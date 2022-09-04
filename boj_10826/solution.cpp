#include <bits/stdc++.h>
using namespace std;

template<typename base_t=unsigned long long, base_t BASE=1ull<<30>
class BigInteger {
 public:
  vector<base_t> data_;
  bool neg_;

  BigInteger() : data_({0}), neg_(false) {}

  BigInteger(int i) : data_({(base_t)std::abs(i)}), neg_(i < 0) {
    fix();
  }

  BigInteger(const string& s) : BigInteger() {
    bool neg = false;
    for (size_t i = 0; i < s.size(); ++i) {
      const char& c = s[i];
      if (i == 0 && c == '-') {
        neg = true;
        continue;
      }
      *this *= 10;
      *this += c - '0';
    }
    neg_ = neg;
  }

  auto operator<=>(const BigInteger& rhs) const {
    if (neg_ && !rhs.neg_) { return -1; }
    if (!neg_ && rhs.neg_) { return 1; }
    int res = 0;
    for (int i = (int)max(data_.size(), rhs.data_.size()); i >= 0; --i) {
      auto l = (size_t)i < data_.size() ? data_[i] : (base_t)0;
      auto r = (size_t)i < rhs.data_.size() ? rhs.data_[i] : (base_t)0;
      if (l < r)	res = -1;
      if (l > r) res = 1;
      if (res != 0) break;
    }
    if (neg_) res *= -1;
    return res;
  }

  BigInteger operator-() const {
    BigInteger res = *this;
    res.neg_ ^= 1;
    return res;
  }

  BigInteger& operator+=(const BigInteger& rhs) {
    if (neg_ != rhs.neg_) {
      *this -= (-rhs);
      return *this;
    }
    if (data_.size() <= rhs.data_.size()) {
      data_.resize(rhs.data_.size() + 1);
    }
    for (size_t i = 0; i < rhs.data_.size(); ++i) {
      data_[i] += rhs.data_[i];
    }
    fix();
    return *this;
  }

  BigInteger& operator-=(const BigInteger& rhs) {
    if (neg_ != rhs.neg_) {
      *this += (-rhs);
      return *this;
    }
    if (this->abs() < rhs.abs()) {
      return *this = -(rhs - (*this));
    }
    for (size_t i = 0; i < rhs.data_.size(); ++i) {
      if (data_[i] < rhs.data_[i]) {
        size_t j = i;
        while (data_[++j] == 0) ;
        while (j != i) { data_[j]--; data_[j-1] += BASE; j--; }
      }
      data_[i] -= rhs.data_[i];
    }
    fix();
    return *this;
  }

  BigInteger& operator*=(const BigInteger& rhs) {
    int N = log2(max(data_.size(), rhs.data_.size()));
    N = 1 << (N + 2);
    vector<C> a(N), b(N);
    for (size_t i = 0; i < data_.size(); ++i) {
      a[i] = {data_[i]};
    }
    for (size_t i = 0; i < rhs.data_.size(); ++i) {
      b[i] = {rhs.data_[i]};
    }
    FFT(a);
    FFT(b);
    for (int i = 0; i < N; ++i) {
      b[i] *= a[i];
    }
    iFFT(b);
    for (int i = 0; i < N; ++i) {
      base_t x = round(b[i].real());
      if (x == 0) 
        continue;
      if (data_.size() <= i) {
        data_.resize(i+1);
      }
      data_[i] = x;
    }
    
    neg_ ^= rhs.neg_;
    return *this;
  }

  BigInteger& operator*=(int rhs) {
    for (auto& i : data_) {
      i *= rhs;
    }
    fix();
    return *this;
  }
  
  BigInteger& operator/=(int rhs) {
    bool neg = rhs < 0;
    for (int i = data_.size() - 1; i > 0; --i) {
      data_[i-1] += data_[i] % rhs * BASE;
      data_[i] /= rhs;
    }
    data_[0] /= rhs;
    neg_ ^= neg;
    fix();
    return *this;
  }

  BigInteger& operator%=(int rhs) {
    bool neg = rhs < 0;
    for (int i = data_.size() - 1; i > 0; --i) {
      data_[i-1] += data_[i] % rhs * BASE;
      data_[i] /= rhs;
    }
    data_[0] %= rhs;
    neg_ ^= neg;
    fix();
    return *this;
  }
  
  bool operator==(const BigInteger& rhs) const { return (*this <=> rhs) == 0; }
  bool operator<(const BigInteger& rhs) const { return (*this <=> rhs) < 0; }
  bool operator>(const BigInteger& rhs) const { return (*this <=> rhs) > 0; }
  BigInteger operator+(const BigInteger& rhs) const { auto res = *this; res += rhs; return res; }
  BigInteger operator-(const BigInteger& rhs) const { auto res = *this; res -= rhs; return res; }
  BigInteger operator*(int rhs) const { auto res = *this; res *= rhs; return res; }
  BigInteger operator/(int rhs) const { auto res = *this; res /= rhs; return res; }
  BigInteger operator%(int rhs) const { auto res = *this; res %= rhs; return res; }

  int sign() const { return neg_ ? -1 : 1; }
  BigInteger abs() const { return neg_ ? -(*this) : *this; }
  int getInt() const { return sign() * (int)data_[0]; }

  friend istream& operator>>(istream& istr, BigInteger& rhs) {
    string s;
    istr >> s;
    rhs = s;
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const BigInteger& rhs) {
    if (rhs == BigInteger(0)) {
      ostr << '0';
      return ostr;
    }
    string s;
    int sign = rhs.sign();
    BigInteger i = rhs.abs();
    while (i > 0) {
      s.push_back(char((i % 10).getInt()) + '0');
      i /= 10;
    }
    if (sign == -1) {
      s.push_back('-');
    }
    reverse(s.begin(), s.end());
    ostr << s;
    return ostr;
  }

 private:
  void fix() {
    for (size_t i = 0; i < data_.size(); ++i) {
      base_t& x = data_[i];
      if (x >= BASE) {
        if (i == data_.size()-1) {
          data_.push_back(x / BASE);
        } else {
          data_[i+1] += x / BASE;
        }
        data_[i] %= BASE;
      }
    }
    shrink();
    if (data_.size() == 1 && data_[0] == 0 && neg_) {
      neg_ ^= 1;
    }
  }
  
  void shrink() {
    int i = data_.size()-1;
    while (i > 0 && data_[i] == 0) {
      i--;
    }
    data_.resize(i+1);
  }

  using C = complex<double>;

  static void FFT(vector<C>& v, bool inv = false) {
    size_t n = v.size();
    for (size_t i = 1, j = 0; i < n; ++i) {
      size_t b = n >> 1;
      while (!((j ^= b) & b))
        b >>= 1;
      if (i < j)
        swap(v[i], v[j]);
    }
    for (size_t k = 1; k < n; k <<= 1) {
      C::value_type a = (inv ? 1.0 : -1.0) * M_PI / (C::value_type)k;
      C w(cos(a), sin(a));
      for (size_t i = 0; i < n; i += (k << 1)) {
        C wp(1, 0);
        for (size_t j = 0; j < k; ++j) {
          C x = v[i + j];
          C y = v[i + j + k] * wp;
          v[i + j] = x + y;
          v[i + j + k] = x - y;
          wp *= w;
        }
      }
    }
    if (inv) {
      for (size_t i = 0; i < n; ++i)
        v[i] /= (C::value_type)n;
    }
  }

  static void iFFT(vector<C>& f) { return FFT(f, 1); }
};

void solve() {
  int N;
  scanf("%d", &N);

  if (N == 0) {
    printf("%d\n", 0);
    return;
  } 
  if (N == 1) {
    printf("%d\n", 1);
    return;
  }

  BigInteger a(0), b(1);
  for (int i = 2; i <= N; ++i) {
    a += b;
    swap(a, b);
  }
  cout << b << "\n";
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
