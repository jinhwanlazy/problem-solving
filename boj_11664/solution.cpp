#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t R, size_t C, typename Derived>
class MatBase {
 public:
  T data_[R * C] = {0};

  MatBase() {}
  MatBase(const Derived& rhs) {
    copy(rhs.data_, rhs.data_ + size(), this->data_);
  }

  constexpr size_t size() const { return R * C; }
  T& at(int r, int c) { return data_[C * r + c]; }
  const T& at(int r, int c) const { return data_[C * r + c]; }
  T& operator[](size_t i) { return data_[i]; }
  const T& operator[](size_t i) const { return data_[i]; }

  Derived operator*(const T& rhs) const {
    Derived res(*this);
    for (size_t i = 0; i < size(); ++i) {
      res.data_[i] *= rhs;
    }
    return res;
  }

  Derived operator-(const Derived& rhs) const {
    Derived res(*this);
    for (size_t i = 0; i < size(); ++i) {
      res.data_[i] -= rhs.data_[i];
    }
    return res;
  }

  Derived operator+(const Derived& rhs) const {
    Derived res(*this);
    for (size_t i = 0; i < size(); ++i) 
      res.data_[i] += rhs.data_[i];
    return res;
  }

  Derived operator%(const Derived& rhs) const {
    Derived res(*this);
    for (size_t i = 0; i < size(); ++i) 
      res.data_[i] += rhs.data_[i];
    return res;
  }

  friend istream& operator>>(istream& istr, MatBase& m) {
    for (size_t i = 0; i < m.size(); ++i) 
      istr >> m.data_[i];
    return istr;
  }
};

template <typename T, size_t R, size_t C>
class Mat : public MatBase<T, R, C, Mat<T, R, C>> {};

template <typename T, size_t R>
class Vec : public MatBase<T, R, 1, Vec<T, R>> {
 public:
  using MatBase<T, R, 1, Vec<T, R>>::MatBase;

  Vec(const MatBase<T, R, 1, Vec<T, R>>& m) {
    copy(m.data_, m.data_ + R, this->data_);
  }

  T& x() { return this->data_[0]; }
  T& y() { return this->data_[1]; }
  T& z() { return this->data_[2]; }
  T& w() { return this->data_[3]; }

  T& at(size_t i) { return this->data_[i]; }
  const T& at(size_t i) const { return this->data_[i]; }

  T squaredNorm() const {
    T res(0);
    for (size_t r = 0; r < R; ++r)
      res += this->data_[r] * this->data_[r];
    return res;
  }

  T squaredNorm(const Vec& rhs) const { return (*this - rhs).squaredNorm(); }
  double norm() const { return sqrt(squaredNorm()); }
  double norm(const Vec& other) const { return norm(*this - other); }

  T dot(const Vec& other) const {
    T res = 0;
    for (size_t i = 0; i < R; ++i) 
      res += this->data_[i] * other.data_[i];
    return res;
  }
};

template <typename T, size_t D>
class Seg {
 public:
  const Vec<T, D>&p, q;
  Seg(const Vec<T, D>& p, const Vec<T, D>& q) : p(p), q(q) {}
  Vec<T, D> vec() const { return q - p; }
};

using Mat3 = Mat<double, 3, 3>;
using Vec3 = Vec<double, 3>;
using Seg3 = Seg<double, 3>;

template <typename T, size_t D>
T distance(const Seg<T, D>& seg, const Vec<T, D>& r) {
  const auto& [p, q] = seg;
  const Vec v = q - p;
  if (v.dot(r - p) <= 0) {
    return (r - p).norm();
  }

  if (-v.dot(r - q) <= 0) {
    return (r - q).norm();
  }
  const double l2 = v.squaredNorm();
  const double t = max(0.0, min(1.0, (r - p).dot(v) / l2));
  const Vec s = seg.p + v * t;
  return (r - s).norm();
}

void solve() {
  Vec3 A, B, C;
  cin >> A >> B >> C;

  Seg3 AB(A, B);
  cout << setprecision(10) << distance(AB, C);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
