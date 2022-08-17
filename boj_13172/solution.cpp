#include <bits/stdc++.h>
using namespace std;

using LL = long long;

template <typename T=LL, T MOD=1000000007>  // Modular Arithmetic Class
class MA {
 public:
  T x_; 
  
  MA() : x_(0) {}
  MA(const T& x) : x_(x) { update(); }

  inline MA operator+(const MA& rhs) const { return MA(x_ + rhs.x_); }
  inline MA& operator+=(const MA& rhs) { x_ += rhs.x_; return update(); }
  inline MA operator-(const MA& rhs) const { return MA(x_ - rhs.x_); }
  inline MA& operator-=(const MA& rhs) { x_ -= rhs.x_; return update(); }
  inline MA operator*(const MA& rhs) const { return MA(x_ * rhs.x_); }
  inline MA& operator*=(const MA& rhs) { x_ *= rhs.x_; return update(); }
  inline MA operator/(const MA& rhs) const { return *this * rhs.inv(); }
  inline MA& operator/=(const MA& rhs) { x_ *= rhs.inv().x_; return update(); }

  MA pow(const T& y) const {
    if (y == 0) return 1;
    if (y == 1) return x_;
    MA res = pow(y / 2);
    res *= res;
    if (y % 2 == 1)
      res *= (*this);
    return res;
  }

  MA inv() const {
    return pow(MOD-2);
  }

  friend istream& operator>>(istream& istr, MA& rhs) { istr >> rhs.x_; return istr; }
  friend ostream& operator<<(ostream& ostr, MA& rhs) { ostr << rhs.x_; return ostr; }

 private:
  MA& update() {
    while (x_ < 0) x_ += MOD;
    x_ = x_ >= MOD ? x_ % MOD : x_;
    return *this;
  }
};

void solve() {
  int M;
  cin >> M;

  MA E;
  while (M--) {
    MA N, S;
    cin >> N >> S;
    E += S / N;
  }

  cout << E << "\n";
}


int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
