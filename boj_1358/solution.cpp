#include <bits/stdc++.h>
using namespace std;

class Vec2 {
 public:
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

  inline T squaredNorm() const { return ((x * x) + (y * y)); }

  inline double length() const { return norm(); }

  inline double length(const Vec2& pos) const {
    return sqrt(squaredLength(pos));
  }

  inline T squaredLength() const { return squaredNorm(); }

  inline T squaredLength(const Vec2& pos) const {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)));
  }

  inline T l1length() const { return abs(x) + abs(y); }

  inline T l1length(const Vec2& pos) const {
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

  inline T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }

  inline T cross(const Vec2& rhs) const { return x * rhs.y - y * rhs.x; }

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
    ostr << setprecision(15) << rhs.x << " " << rhs.y;
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
  // +1 --> Clockwise
  // -1 --> Counterclockwise
  static int orientation(const Vec2& p, const Vec2& q, const Vec2& r) {
    // https://www.geeksforgeeks.org/orientation-3-ordered-points/
    T val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) {
      return 0;
    }
    return val > 0 ? 1 : -1;
  }

  // Given three colinear points p, q, r, the function checks if
  // point q lies on line segment 'pr'
  static bool onSegment(const Vec2 p, const Vec2 q, const Vec2 r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
  }
};

class Circle {
  using T = Vec2::T;

  Vec2 center;
  T radius;

 public:
  inline bool operator==(const Circle& rhs) const {
    return ((center == rhs.center) && (radius == rhs.radius));
  }

 public:
  double area() const { return radius * radius * M_PI; }

 public:
  bool contains(const Vec2& rhs) const {
    Vec2 d = rhs - center;
    return rhs.squaredLength(center) <= radius * radius;
  }

  bool contains(const Circle& rhs) const {
    return radius >= (center.length(rhs.center) + rhs.radius);
  }

  bool overlaps(const Circle& rhs) const {
    double d = center.length(rhs.center);
    return d < radius + rhs.radius;
    // return abs(radius - rhs.radius) < d && d < radius + rhs.radius;
  }

  optional<pair<Vec2, Vec2>> intersection(const Circle& rhs) const {
    // http://paulbourke.net/geometry/circlesphere/
    if (*this == rhs) {
      return nullopt;
    }
    const Vec2& p0 = this->center;
    const Vec2& p1 = rhs.center;
    double r0 = this->radius;
    double r1 = rhs.radius;
    double d = p0.length(p1);

    if (d >= r0 + r1) {
      return nullopt;
    }
    if (d <= abs(r0 - r1)) {
      return nullopt;
    }

    double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    double h = sqrt(r0 * r0 - a * a);
    Vec2 p2 = p0 + (p1 - p0) * (a / d);
    Vec2 diff = Vec2{p1.y - p0.y, p1.x - p0.x} * h / d;
    return make_pair(p2 + diff, p2 - diff);
  }

  double overlappingArea(const Circle& rhs) const {
    if (!overlaps(rhs)) {
      return 0;
    }
    if (rhs.contains(*this)) {
      return area();
    }
    if (this->contains(rhs)) {
      return rhs.area();
    }
    const double& r0 = radius;
    const double& r1 = rhs.radius;
    const double d = center.length(rhs.center);
    const double angle0 = acos((r0 * r0 + d * d - r1 * r1) / (2 * r0 * d));
    const double angle1 = acos((r1 * r1 + d * d - r0 * r0) / (2 * r1 * d));
    const double rr0 = radius * radius;
    const double rr1 = rhs.radius * rhs.radius;

    double ans = +rr0 * angle0 - rr0 * sin(2 * angle0) * 0.5 + rr1 * angle1 -
                 rr1 * sin(2 * angle1) * 0.5;
    return ans;
  }

 public:
  friend istream& operator>>(istream& istr, Circle& rhs) {
    istr >> rhs.center.x >> rhs.center.y >> rhs.radius;
    return istr;
  }

 public:
  Circle() : center(0, 0), radius(T(0)) {}

  Circle(T x, T y, T r) : center(x, y), radius(r) {}

  Circle(const Circle& rhs) : center(rhs.center), radius(rhs.radius) {}

  ~Circle() {}
};

class Square {
  using T = Vec2::T;

  T left;
  T right;
  T bottom;
  T top;

 public:
  inline bool operator==(const Square& rhs) const {
    return (top == rhs.top && bottom == rhs.bottom && left == rhs.left &&
            right == rhs.right);
  }

 public:
  T area() const { return (top - bottom) * (right - left); }

 public:
  bool contains(const Vec2& rhs) const {
    return left <= rhs.x && rhs.x <= right && bottom <= rhs.y && rhs.y <= top;
  }

 public:
  friend istream& operator>>(istream& istr, Square& rhs) {
    istr >> rhs.left >> rhs.right >> rhs.bottom >> rhs.top;
    return istr;
  }

 public:
  Square() : left(0), right(1), bottom(0), top(1) {}

  Square(T l, T r, T b, T t) : left(l), right(r), bottom(b), top(t) {}

  ~Square() {}
};

int main() {
  int W, H, X, Y, P;
  scanf("%d %d %d %d %d", &W, &H, &X, &Y, &P);

  Circle c1(X, Y + H / 2, H / 2);
  Circle c2(X + W, Y + H / 2, H / 2);
  Square s(X, X + W, Y, Y + H);

  int ans = 0;
  for (int i = 0; i < P; ++i) {
    Vec2 p;
    cin >> p;
    ans += c1.contains(p) || c2.contains(p) || s.contains(p);
  }
  cout << ans << "\n";

  return 0;
}
