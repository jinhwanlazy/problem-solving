#include <bits/stdc++.h>
using namespace std;

template <unsigned BASE=100000000> 
class BigInteger {
  using base_t = unsigned long long;
 public:
  vector<base_t> data_;
  bool neg_;

  BigInteger() : data_({0}), neg_(false) {}

  BigInteger(long long i) : data_({base_t(i < 0 ? -i : i)}), neg_(i < 0) { fixOverflow(); }

  BigInteger(const string& s) : BigInteger() {
    if (s == "0") 
      return;
    neg_ = s[0] == '-';
    int stride = int(log10(BASE));
    int start = neg_ ? 1 : 0;
    data_.clear();
    for (int r = (int)s.size(); r > start; r -= stride) {
      int l = max(start, r - stride);
      string chunk = s.substr(l, r - l);
      data_.push_back(stoi(chunk));
    }
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
    data_.reserve(rhs.data_.size() + 1);
    for (size_t i = 0; i < rhs.data_.size(); ++i) {
      if (data_.size() < i + 1) 
        data_.resize(i+1, 0);
      data_[i] += rhs.data_[i];
    }
    fixOverflow();
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
    shrinkToFit();
    return *this;
  }

  BigInteger& operator*=(const BigInteger& rhs) {
    size_t N = log2(max(data_.size(), rhs.data_.size()));
    N = 1 << (N + 2);
    vector<C> a(N), b(N);
    for (size_t i = 0; i < data_.size(); ++i) {
      a[i] = {(C::value_type)data_[i], 0};
    }
    for (size_t i = 0; i < rhs.data_.size(); ++i) {
      b[i] = {(C::value_type)rhs.data_[i], 0};
    }
    FFT(a);
    FFT(b);
    for (size_t i = 0; i < N; ++i) {
      b[i] *= a[i];
    }
    iFFT(b);
    fill(data_.begin(), data_.end(), 0);
    data_.reserve(N+1);
    for (size_t i = 0; i < N; ++i) {
      base_t x = round(b[i].real());
      if (x == 0) 
        continue;
      if (data_.size() <= i) 
        data_.resize(i+1, 0);
      data_[i] = x;
    }
    fixOverflow();
    neg_ ^= rhs.neg_;
    return *this;
  }

  BigInteger& operator*=(int rhs) {
    for (auto& i : data_) 
      i *= rhs;
    fixOverflow();
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
    shrinkToFit();
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
    shrinkToFit();
    return *this;
  }
  
  bool operator==(const BigInteger& rhs) const { return (*this <=> rhs) == 0; }
  bool operator<(const BigInteger& rhs) const { return (*this <=> rhs) < 0; }
  bool operator>(const BigInteger& rhs) const { return (*this <=> rhs) > 0; }
  BigInteger operator+(const BigInteger& rhs) const { auto res = *this; res += rhs; return res; }
  BigInteger operator-(const BigInteger& rhs) const { auto res = *this; res -= rhs; return res; }
  BigInteger operator*(const BigInteger& rhs) const { auto res = *this; res *= rhs; return res; }
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

    ios init(NULL);
    init.copyfmt(ostr);

    double log10base = log10(BASE);
    if (rhs.neg_) {
      ostr << '-';
    }
    for (int i = (int)rhs.data_.size() - 1; i >= 0; --i) {
      if (i <= (int)rhs.data_.size() - 2)
        ostr << std::setw(int(log10base)) << std::setfill('0');
      ostr << rhs.data_[i];
    }
    ostr.copyfmt(init);
    return ostr;
  }

  void show() const {
    cout << "BigInteger(sign: " << sign() << ", vals: ";
    for (unsigned c : data_) {
      cout << c << ", ";
    }
    cout << ")\n";
  }

 private:
  void fixOverflow() {
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
  }
  
  void shrinkToFit() {
    int i = data_.size()-1;
    for (; i > 0 && data_[i] == 0; --i);
    data_.resize(i+1);
    if (data_.size() == 1 && data_[0] == 0 && neg_) {
      neg_ ^= 1;
    }
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
  BigInteger<100> a, b;
  cin >> a >> b;
  cout << a * b << "\n";
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
