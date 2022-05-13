#include <bits/stdc++.h>
using namespace std;

class Point2 {
  using T = double;

 public:
  T x;
  T y;

 public:
  inline Point2& operator=(const Point2& rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

 public:
  inline bool operator==(const Point2& rhs) const {
    return ((x == rhs.x) && (y == rhs.y));
  }

  inline bool operator!=(const Point2& rhs) const { return !(operator==(rhs)); }

  inline Point2 operator+(const Point2& rhs) const {
    return Point2(x + rhs.x, y + rhs.y);
  }

  inline Point2 operator-(const Point2& rhs) const {
    return Point2(x - rhs.x, y - rhs.y);
  }

  inline Point2 operator*(T rhs) const {
    return Point2(T(x * rhs), T(y * rhs));
  }

  inline Point2 operator/(T rhs) const {
    return Point2(T(x / rhs), T(y / rhs));
  }

  inline Point2 operator-() const { return Point2(-x, -y); }

  inline Point2& operator+=(const Point2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Point2& operator-=(const Point2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  inline Point2& operator*=(T rhs) {
    x = T(x * rhs);
    y = T(y * rhs);
    return *this;
  }

  inline Point2& operator/=(T rhs) {
    x = T(x / rhs);
    y = T(y / rhs);
    return *this;
  }

 public:
  inline double norm() const { return sqrt(squaredNorm()); }

  inline double squaredNorm() const { return ((x * x) + (y * y)); }

  inline double length(const Point2& pos) const {
    return sqrt(squaredLength(pos));
  }

  inline double squaredLength(const Point2& pos) const {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)));
  }

  inline double l1() const { return abs(x) + abs(y); }

  inline double l1(const Point2& pos) const {
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

  inline Point2 normalized() const {
    Point2 n(*this);
    n.normalize();
    return n;
  }

 public:
  static const Point2& xAxis() {
    static Point2 vec(1, 0);
    return vec;
  }
  static const Point2& yAxis() {
    static Point2 vec(0, 1);
    return vec;
  }
  static const Point2& zero() {
    static Point2 vec(0, 0);
    return vec;
  }
  friend ostream& operator<<(ostream& ostr, const Point2& rhs) {
    ostr << "Point2[" << rhs.x << ", " << rhs.y << "]";
    return ostr;
  }

  friend istream& operator>>(istream& istr, Point2& rhs) {
    istr >> rhs.x >> rhs.y;
    return istr;
  }

 public:
  Point2() : x(T(0)), y(T(0)) {}

  Point2(T x_, T y_) : x(x_), y(y_) {}

  Point2(const Point2& rhs) : x(rhs.x), y(rhs.y) {}

  ~Point2() {}
};

double shoelace(const vector<Point2>& points) {
  double res = 0;
  for (int i = 0; i <= points.size(); ++i) {
    res += points[i].x * points[(i + 1) % points.size()].y;
    res -= points[i].y * points[(i + 1) % points.size()].x;
  }
  return 0.5 * abs(res);
}

int main() {
  int N;
  scanf("%d", &N);

  vector<Point2> points(N);
  for (int i = 0; i < N; ++i) {
    cin >> points[i];
  }

  printf("%.1lf\n", shoelace(points));
  return 0;
}
