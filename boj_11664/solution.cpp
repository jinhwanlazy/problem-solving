#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t R, size_t C>
class Mat {
 public:
  T data_[R * C] = {0};

  Mat() {}
  Mat(const Mat& rhs) { copy(rhs.data_, rhs.data_ + size(), this->data_); }
  Mat(std::initializer_list<T> l) { copy(l.begin(), l.end(), this->data_); }

  constexpr bool isVector() const { return (C == 1); }
  constexpr size_t size() const { return R * C; }
  constexpr void throwIfNotVector() const {
    if constexpr (C != 1)
      throw runtime_error("the method is defined only for vector");
  }
  constexpr void throwIfNotSquare() const {
    if constexpr (R != C) 
      throw runtime_error("the method is defined only for square matrix");
  }
  void forEach(const function<void(size_t i)>& fn) {
    for (size_t i = 0; i < size(); ++i)
      fn(i);
  }

  T& operator()(size_t r, size_t c) { return data_[C * r + c]; }
  const T& operator()(size_t r, size_t c) const { return data_[C * r + c]; }
  const T& at(size_t r, size_t c) const { return data_[C * r + c]; }

  Mat& operator+=(const T& rhs) { forEach([&](size_t i) { this->data_[i] += rhs; }); return *this; }
  Mat& operator-=(const T& rhs) { forEach([&](size_t i) { this->data_[i] -= rhs; }); return *this; }
  Mat& operator*=(const T& rhs) { forEach([&](size_t i) { this->data_[i] *= rhs; }); return *this; }
  Mat& operator/=(const T& rhs) { forEach([&](size_t i) { this->data_[i] /= rhs; }); return *this; }
  Mat& operator%=(const T& rhs) { forEach([&](size_t i) { this->data_[i] %= rhs; }); return *this; }

  Mat operator+(const T& rhs) const { Mat res(*this); res += rhs; return res; }
  Mat operator-(const T& rhs) const { Mat res(*this); res -= rhs; return res; }
  Mat operator*(const T& rhs) const { Mat res(*this); res *= rhs; return res; }
  Mat operator/(const T& rhs) const { Mat res(*this); res /= rhs; return res; }
  Mat operator%(const T& rhs) const { Mat res(*this); res %= rhs; return res; }

  Mat& operator+=(const Mat& rhs) { forEach([&](size_t i) { this->data_[i] += rhs.data_[i]; }); return *this; };
  Mat& operator-=(const Mat& rhs) { forEach([&](size_t i) { this->data_[i] -= rhs.data_[i]; }); return *this; };

  Mat operator+(const Mat& rhs) const { Mat res(*this); res += rhs; return res; };
  Mat operator-(const Mat& rhs) const { Mat res(*this); res -= rhs; return res; };

  template<typename U, size_t R2, size_t C2>
  Mat<T, R, C2> operator*(const Mat<U, R2, C2>& rhs) const { 
    static_assert (C == R2, "shape not compatible");
    Mat<T, R, C2> res;
    for (size_t i = 0; i < R; ++i) {
      for (size_t j = 0; j < C2; ++j) {
        for (size_t k = 0; k < C; ++k) {
          res(i, j) = (*this)(i, k) * rhs(k, j);
        }
      }
    }
    return res;
  }

  Mat<T, C, R> t() const {
    Mat<T, C, R> res;
    for (size_t i = 0; i < C; ++i) {
      for (size_t j = 0; j < R; ++j) {
        res(i, j) = (*this)(j, i);
      }
    }
    return res;
  } 

  T det() const {
    if constexpr (R == 2 && C == 2) {
      return at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
    } else if constexpr (R == 3 && C == 3) {
      const T c00 = at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1);
      const T c10 = at(1, 2) * at(2, 0) - at(1, 0) * at(2, 2);
      const T c20 = at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0);
      return at(0, 0) * c00 + at(0, 1) * c10 + at(0, 2) * c20;
    } else {
      throw runtime_error("not implemented");
    }
  }

  friend istream& operator>>(istream& istr, Mat& m) { 
    m.forEach([&](size_t i) { istr >> m.data_[i]; });
    return istr;
  }

  T& operator()(size_t i) { throwIfNotVector(); return data_[i]; }
  const T& operator()(size_t i) const { throwIfNotVector(); return data_[i]; }
  T& x() { throwIfNotVector(); return data_[0]; }
  T& y() { throwIfNotVector(); return data_[1]; }
  T& z() { throwIfNotVector(); return data_[2]; }
  T& w() { throwIfNotVector(); return data_[3]; }

  T dot(const Mat& other) const {
    throwIfNotVector();
    T res = 0;
    for (size_t i = 0; i < R; ++i)
      res += this->data_[i] * other.data_[i];
    return res;
  }

  T squaredNorm() const {
    throwIfNotVector();
    T res(0);
    for (size_t r = 0; r < R; ++r)
      res += this->data_[r] * this->data_[r];
    return res;
  }

  T squaredNorm(const Mat& rhs) const {
    throwIfNotVector();
    return (*this - rhs).squaredNorm();
  }

  double norm() const { throwIfNotVector(); return sqrt(squaredNorm()); }
  double norm(const Mat& other) const { throwIfNotVector(); return norm(*this - other); }

  Mat inverse() const {
    throwIfNotSquare();
    if constexpr (R == 2) {
      T det = at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
      if (det == 0) {
        return Mat();
      }
      double invDet = 1.0 / det;
      return Mat((T)(invDet * at(1, 1)), (T)(-invDet * at(0, 1)),
                 (T)(-invDet * at(1, 0)), (T)(invDet * at(0, 0)));
    } else if constexpr (R == 3) {
      T c00 = at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1);
      T c10 = at(1, 2) * at(2, 0) - at(1, 0) * at(2, 2);
      T c20 = at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0);
      T det = at(0, 0) * c00 + at(0, 1) * c10 + at(0, 2) * c20;
      if (det == 0) {
        return Mat();
      }
      double invDet = 1.0 / det;
      return Mat((T)(invDet * (c00)),
                 (T)(invDet * (at(0, 2) * at(2, 1) - at(0, 1) * at(2, 2))),
                 (T)(invDet * (at(0, 1) * at(1, 2) - at(0, 2) * at(1, 1))),
                 (T)(invDet * (c10)),
                 (T)(invDet * (at(0, 0) * at(2, 2) - at(0, 2) * at(2, 0))),
                 (T)(invDet * (at(0, 2) * at(1, 0) - at(0, 0) * at(1, 2))),
                 (T)(invDet * (c20)),
                 (T)(invDet * (at(0, 1) * at(2, 0) - at(0, 0) * at(2, 1))),
                 (T)(invDet * (at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0))));
    } else {
      throw runtime_error("not implemented");
    }
  }
};

using Mat3 = Mat<double, 3, 3>;
using Vec3 = Mat<double, 3, 1>;

class Seg3 {
 public:
  const Vec3 &p, q;
  Seg3(const Vec3& p, const Vec3& q) : p(p), q(q) {}
  Vec3 vec() const { return q - p; }
};

double distance(const Seg3& seg, const Vec3& r) {
  const auto& [p, q] = seg;
  const Vec3 v = q - p;
  if (v.dot(r - p) <= 0) {
    return (r - p).norm();
  }

  if (-v.dot(r - q) <= 0) {
    return (r - q).norm();
  }
  const double l2 = v.squaredNorm();
  const double t = max(0.0, min(1.0, (r - p).dot(v) / l2));
  const Vec3 s = seg.p + v * t;
  return (r - s).norm();
}

void solve() {
  Vec3 A, B, C;
  cin >> A >> B >> C;

  Seg3 AB(A, B);
  cout << setprecision(10) << distance(AB, C) << "\n";
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
