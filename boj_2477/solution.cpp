#include <bits/stdc++.h>
using namespace std;

class Vec2 {
 public:
  using T = long long;

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

long long shoelace(const vector<Vec2>& points) {
  double res = 0;
  for (int i = 0; i <= points.size(); ++i) {
    res += points[i].x * points[(i + 1) % points.size()].y;
    res -= points[i].y * points[(i + 1) % points.size()].x;
  }
  return abs(res) / 2;
}

int main() {
  int K;
  scanf("%d", &K);

  vector<Vec2> points;
  points.push_back(Vec2(0, 0));
  for (int i = 0; i < 6; ++i) {
    int dir;
    int v;
    cin >> dir >> v;
    switch (dir) {
      case 1:
        points.push_back(points.back() + Vec2(v, 0));
        break;
      case 2:
        points.push_back(points.back() + Vec2(-v, 0));
        break;
      case 3:
        points.push_back(points.back() + Vec2(0, -v));
        break;
      case 4:
        points.push_back(points.back() + Vec2(0, v));
        break;
      default:
        break;
    }
  }
  cout << shoelace(points) * K << "\n";

  return 0;
}
