#include <bits/stdc++.h>
using namespace std;

class Vec2 {
public:
  using T = double;
  T x;
  T y;

public:
  inline Vec2& operator=(const Vec2& rhs) { x = rhs.x; y = rhs.y; return *this; }

public:
  inline bool operator==(const Vec2& rhs) const { return ((x == rhs.x) && (y == rhs.y)); }
  inline bool operator!=(const Vec2& rhs) const { return !(operator==(rhs)); }
  inline Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
  inline Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
  inline Vec2 operator*(T rhs) const { return Vec2(T(x * rhs), T(y * rhs)); }
  inline Vec2 operator/(T rhs) const { return Vec2(T(x / rhs), T(y / rhs)); }
  inline Vec2 operator-() const { return Vec2(-x, -y); }
  inline Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
  inline Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
  inline Vec2& operator*= (T rhs) { x = T(x * rhs); y = T(y * rhs); return *this; }
  inline Vec2& operator/= (T rhs) { x = T(x / rhs); y = T(y / rhs); return *this; }

  inline double norm() const { return sqrt(squaredNorm()); }
  inline T squaredNorm() const { return ((x * x) + (y * y)); }
  inline T norm1() const { return abs(x) + abs(y); }
  inline void normalize()
  {
    double l = norm();
    if (l < numeric_limits<double>::epsilon()) {
      x = 0;
      y = 0;
    }
    else {
      x = (T)(x / l);
      y = (T)(y / l);
    }
  }

  inline Vec2 normalized() const
  {
    Vec2 n(*this);
    n.normalize();
    return n;
  }

  inline bool close(const Vec2& rhs,
                    const double span = 1.0,
                    const double tol = 1e-20) const {
    return ((*this - rhs).squaredNorm() / span) < tol;
  }

  inline T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }
  inline T cross(const Vec2& rhs) const { return x * rhs.y - y * rhs.x; }
  inline double angle(const Vec2& rhs) const
  {
    double sqlen = squaredNorm();
    double sqlen2 = rhs.squaredNorm();

    if (sqlen == 0.0 || sqlen2 == 0.0) {
      return 0.0;
    }

    double val = dot(rhs) / sqrt(sqlen) / sqrt(sqlen2);
    val = std::max(-1.0, min(val, 1.0));
    return acos(val);
  }

public:
  static const Vec2& xAxis() { static Vec2 vec(1, 0); return vec; }
  static const Vec2& yAxis() { static Vec2 vec(0, 1); return vec; }
  static const Vec2& zero() { static Vec2 vec(0, 0); return vec; }
  friend ostream& operator<<(ostream& ostr, const Vec2& rhs) {
    ostr << setprecision(15) << rhs.x << " " << rhs.y;
    return ostr;
  }

  friend istream& operator>>(istream& istr, Vec2& rhs) {
    istr >> rhs.x >> rhs.y;
    return istr;
  }

  friend bool operator<(const Vec2& lhs, const Vec2& rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
  }

public:
  Vec2() : x(T(0)), y(T(0)) {}
  Vec2(T x_, T y_) : x(x_), y(y_) {}
  Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y) {}
  ~Vec2() {}
};

class Circle
{
public:
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
    return (rhs - center).squaredNorm() <= radius * radius;
  }

  bool contains(const Circle& rhs) const {
    return radius >= ((center - rhs.center).norm() + rhs.radius);
  }

  bool overlaps(const Circle& rhs) const {
    double d = (center - rhs.center).norm();
    return d < radius + rhs.radius;
    //return abs(radius - rhs.radius) < d && d < radius + rhs.radius;
  }

  optional<pair<Vec2, Vec2>> intersection(const Circle& rhs) const {
    // http://paulbourke.net/geometry/circlesphere/
    if (*this == rhs) {
      return make_pair(center + Vec2{radius, 0}, center + Vec2{0, radius});
    }
    const Vec2& p0 = this->center;
    const Vec2& p1 = rhs.center;
    double r0 = this->radius;
    double r1 = rhs.radius;
    double d = (p0 - p1).norm();

    if (d > r0 + r1) {
      return nullopt;
    }
    if (d < abs(r0 - r1)) {
      return nullopt;
    }
    double a = (r0*r0 - r1*r1 + d*d) / (2 * d);
    double h = sqrt(r0*r0 - a*a);
    Vec2 p2 = p0 + (p1 - p0) * (a / d);
    Vec2 diff = Vec2{p1.y - p0.y, -p1.x + p0.x} * h / d;
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
    const double d = (center - rhs.center).norm();
    const double angle0 = acos((r0 * r0 + d * d - r1 * r1) / (2 * r0 * d));
    const double angle1 = acos((r1 * r1 + d * d - r0 * r0) / (2 * r1 * d));
    const double rr0 = radius * radius;
    const double rr1 = rhs.radius * rhs.radius;

    double ans = 
      + rr0 * angle0 - rr0 * sin(2*angle0) * 0.5
      + rr1 * angle1 - rr1 * sin(2*angle1) * 0.5;
    return ans;
  }

public:
  friend istream& operator>>(istream& istr, Circle& rhs) {
    istr >> rhs.center.x >> rhs.center.y >> rhs.radius;
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const Circle& rhs) {
    ostr << "Circle(p=" << rhs.center << ", " << "r=" << rhs.radius << ")";
    return ostr;
  }

public:
  Circle() : center(0, 0), radius(T(0)) {}
  Circle(T x, T y, T r) : center(x, y), radius(r) {}
  Circle(const Circle& rhs) : center(rhs.center), radius(rhs.radius) {}
  ~Circle() {}
};


void solve() {
  int N;
  cin >> N;

  set<Vec2> intersections;
  vector<Circle> cs(N);
  for (int i = 0; i < N; ++i) {
    cin >> cs[i];

    for (int j = 0; j < i; ++j) {
      auto ps = cs[i].intersection(cs[j]);
      if (ps) {
        intersections.insert(ps->first);
        intersections.insert(ps->second);
      }
    }
  }

  auto circleSD = [](const Circle& c, const Vec2& p) -> double {
    //return (c.center - p).norm() - c.radius;
    return (c.center - p).squaredNorm() - c.radius * c.radius;
  };

  auto circlesSD = [&](const vector<Circle>& cs, const Circle& except,
                       const Vec2& p) -> double {
    double sd = numeric_limits<double>::max();
    for (const auto& c : cs) {
      if (c == except) {
        continue;
      }
      sd = min(sd, circleSD(c, p));
    }
    return sd;
  };

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    const auto & c = cs[i];
    double sd = circlesSD(cs, c, c.center);
    if (sd >= 0) {
      continue;
    }

    bool isNodap = true;
    for (const auto& p : intersections) {
      double sd = circleSD(c, p);
      //cout << p << ", sd: " << sd << "\n";
      if (sd < 0) {
        if (circlesSD(cs, c, p) >= -1e-9)  {
          isNodap = false;
          break;
        }
      }
      if (sd == 0) {
        if (circlesSD(cs, c, p) > 0)  {
          isNodap = false;
          break;
        }
      }
    }
    //if (isNodap) 
      //cout << c << " is nodap\n";
    ans += isNodap;
  }
  cout << ans << "\n";
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
