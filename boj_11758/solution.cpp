#include <bits/stdc++.h>
using namespace std;

class Vec2 {
  using T = double;

 public:
  T x;
  T y;

 public:
  inline Vec2& operator=(const Vec2& rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

 public:
  inline bool operator==(const Vec2& rhs) const {
    return ((x == rhs.x) && (y == rhs.y));
  }

  inline bool operator!=(const Vec2& rhs) const { return !(operator==(rhs)); }

  inline Vec2 operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
  }

  inline Vec2 operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
  }

  inline Vec2 operator*(T rhs) const { return Vec2(T(x * rhs), T(y * rhs)); }

  inline Vec2 operator/(T rhs) const { return Vec2(T(x / rhs), T(y / rhs)); }

  inline Vec2 operator-() const { return Vec2(-x, -y); }

  inline Vec2& operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Vec2& operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  inline Vec2& operator*=(T rhs) {
    x = T(x * rhs);
    y = T(y * rhs);
    return *this;
  }

  inline Vec2& operator/=(T rhs) {
    x = T(x / rhs);
    y = T(y / rhs);
    return *this;
  }

 public:
  inline double norm() const { return sqrt(squaredNorm()); }

  inline double squaredNorm() const { return ((x * x) + (y * y)); }

  inline double length(const Vec2& pos) const {
    return sqrt(squaredLength(pos));
  }

  inline double squaredLength(const Vec2& pos) const {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)));
  }

  inline double l1length() const { return abs(x) + abs(y); }

  inline double l1length(const Vec2& pos) const {
    return abs(x - pos.x) + abs(y - pos.x);
  }

  inline void normalize() {
    double l = norm();
    if (l < numeric_limits<double>::epsilon()) {
      x = 0;
      y = 0;
    } else {
      x = (T)(x / l);
      y = (T)(y / l);
    }
  }

  inline Vec2 normalized() const {
    Vec2 n(*this);
    n.normalize();
    return n;
  }

 public:
  static const Vec2& xAxis() {
    static Vec2 vec(1, 0);
    return vec;
  }
  static const Vec2& yAxis() {
    static Vec2 vec(0, 1);
    return vec;
  }
  static const Vec2& zero() {
    static Vec2 vec(0, 0);
    return vec;
  }
  friend ostream& operator<<(ostream& ostr, const Vec2& rhs) {
    ostr << "Vec2[" << rhs.x << ", " << rhs.y << "]";
    return ostr;
  }

  friend istream& operator>>(istream& istr, Vec2& rhs) {
    istr >> rhs.x >> rhs.y;
    return istr;
  }

 public:
  Vec2() : x(T(0)), y(T(0)) {}

  Vec2(T x_, T y_) : x(x_), y(y_) {}

  Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y) {}

  ~Vec2() {}

 public:
  // To find orientation of ordered triplet (p, q, r).
  // The function returns following values
  // 0 --> p, q and r are colinear
  // 0 < --> Clockwise
  // 0 > --> Counterclockwise
  static double orientation(const Vec2& p, const Vec2& q, const Vec2& r) {
    // https://www.geeksforgeeks.org/orientation-3-ordered-points/
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return val;
  }
};

int main() {
  Vec2 a, b, c;
  cin >> a >> b >> c;

  auto o = Vec2::orientation(a, b, c);
  if (o == 0) {
    cout << 0;
  } else if (o > 0) {
    cout << -1;
  } else {
    cout << 1;
  }
  return 0;
}
